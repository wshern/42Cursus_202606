/* main.c -- test harness for get_next_line, optionally printing
 *           through ft_printf instead of printf.
 *
 * build (printf, default -- no ft_printf needed):
 *   cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
 *      get_next_line.c get_next_line_utils.c main.c -o gnl
 *
 * build (ft_printf as the printer, plus a comparison suite):
 *   cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -D USE_FT_PRINTF \
 *      -I../ft_printf get_next_line.c get_next_line_utils.c main.c \
 *      ../ft_printf/libftprintf.a -o gnl
 *
 * run:
 *   ./gnl              gnl tests, then the ft_printf comparison
 *   ./gnl -p           ft_printf comparison only
 *   ./gnl -            read from stdin   (printf 'a\nb' | ./gnl -)
 *   ./gnl file.txt     one specific file, no pass/fail verdict
 */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

#ifdef USE_FT_PRINTF
# include "ft_printf.h"
# define PF ft_printf
#else
# define PF printf
#endif

/* ft_printf writes straight to fd 1; printf goes through a buffer.
 * Mixing them without flushing scrambles the order of the output.
 * Anywhere the two appear near each other, flush first. */
static void	sync_out(void)
{
	fflush(stdout);
}

/* ------------------------------------------------------------------ */
/* get_next_line tests                                                 */
/* ------------------------------------------------------------------ */

/* Print a line with its bounds visible, so a missing or extra '\n'
 * cannot hide. */
static void	show(int n, char *line)
{
	int	i;

	if (!line)
	{
		PF("  [%d] NULL\n", n);
		return ;
	}
	PF("  [%d] \"", n);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			PF("\\n");
		else if (line[i] == '\t')
			PF("\\t");
		else
			PF("%c", line[i]);
		i++;
	}
	PF("\"\n");
}

/* Read a descriptor to exhaustion. Returns how many non-NULL lines
 * came back. Every line is freed. */
static int	drain(int fd)
{
	char	*line;
	int		n;

	n = 0;
	line = get_next_line(fd);
	while (line)
	{
		show(n, line);
		free(line);
		n++;
		line = get_next_line(fd);
	}
	show(n, NULL);
	return (n);
}

/* Write a fixture file so the tests are self-contained. */
static void	make_file(const char *path, const char *content, int len)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		PF("cannot create %s\n", path);
		return ;
	}
	write(fd, content, len);
	close(fd);
}

/* A negative `expected` means "no expectation" -- used for a file the
 * caller named on the command line, whose line count is unknown.
 * Without this guard the count could never equal the sentinel and
 * every such run printed MISMATCH. */
static void	run_case(const char *label, const char *path, int expected)
{
	int	fd;
	int	got;

	if (expected < 0)
		PF("== %s\n", label);
	else
		PF("== %s (expect %d lines)\n", label, expected);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		PF("  open failed\n\n");
		return ;
	}
	got = drain(fd);
	close(fd);
	if (expected < 0)
		PF("  -> %d lines\n\n", got);
	else if (got == expected)
		PF("  -> %d lines  OK\n\n", got);
	else
		PF("  -> %d lines  MISMATCH\n\n", got);
}

static void	gnl_suite(void)
{
	PF("BUFFER_SIZE = %d\n\n", BUFFER_SIZE);
	make_file("t_empty.txt", "", 0);
	make_file("t_nonl.txt", "no newline at all", 17);
	make_file("t_onlynl.txt", "\n", 1);
	make_file("t_nls.txt", "\n\n\n", 3);
	make_file("t_plain.txt", "one\ntwo\nthree\n", 14);
	make_file("t_tail.txt", "one\ntwo\nthree", 13);
	make_file("t_blank.txt", "a\n\nb\n", 5);
	make_file("t_long.txt",
		"0123456789012345678901234567890123456789012345678901234567890123456789\nx\n",
		73);
	run_case("empty file", "t_empty.txt", 0);
	run_case("no trailing newline", "t_nonl.txt", 1);
	run_case("single newline", "t_onlynl.txt", 1);
	run_case("three newlines", "t_nls.txt", 3);
	run_case("normal file", "t_plain.txt", 3);
	run_case("last line unterminated", "t_tail.txt", 3);
	run_case("blank line in middle", "t_blank.txt", 3);
	run_case("line longer than buffer", "t_long.txt", 2);
	PF("== invalid fd -1 (expect NULL)\n");
	show(0, get_next_line(-1));
	PF("\n== closed fd (expect NULL)\n");
	show(0, get_next_line(4242));
	PF("\n");
}

/* ------------------------------------------------------------------ */
/* ft_printf tests                                                     */
/* ------------------------------------------------------------------ */

#ifdef USE_FT_PRINTF

static int	g_fails;
static int	g_total;

/* Run one format through both functions. The two outputs sit side by
 * side inside brackets so any difference in the printed text is
 * visible, and the return values are compared automatically. */
# define CASE(label, ...)                                             \
	do {                                                              \
		int	r_ft;                                                     \
		int	r_std;                                                    \
		printf("  %-24s ft[", label);                                 \
		sync_out();                                                   \
		r_ft = ft_printf(__VA_ARGS__);                                \
		printf("] std[");                                             \
		r_std = printf(__VA_ARGS__);                                  \
		printf("] ret %d/%d %s\n", r_ft, r_std,                       \
			r_ft == r_std ? "" : "<<< MISMATCH");                     \
		sync_out();                                                   \
		if (r_ft != r_std)                                            \
			g_fails++;                                                \
		g_total++;                                                    \
	} while (0)

static void	suite_basic(void)
{
	printf("-- no conversion\n");
	CASE("plain text", "hello");
	CASE("percent", "100%%");
	CASE("two percents", "a%%b%%c");
	printf("-- %%c\n");
	CASE("c letter", "%c", 'A');
	CASE("c digit", "%c", '7');
	CASE("c null byte", "%c", '\0');
	CASE("c high byte", "%c", (char)200);
	printf("-- %%s\n");
	CASE("s normal", "%s", "forty two");
	CASE("s empty", "%s", "");
	CASE("s NULL", "%s", (char *)NULL);
	CASE("s with percent", "%s", "50%");
}

static void	suite_numbers(void)
{
	printf("-- %%d and %%i\n");
	CASE("d zero", "%d", 0);
	CASE("d positive", "%d", 42);
	CASE("d negative", "%d", -42);
	CASE("d INT_MAX", "%d", INT_MAX);
	CASE("d INT_MIN", "%d", INT_MIN);
	CASE("i negative", "%i", -1);
	printf("-- %%u\n");
	CASE("u zero", "%u", 0u);
	CASE("u max", "%u", UINT_MAX);
	CASE("u from -1", "%u", (unsigned int)-1);
	printf("-- %%x and %%X\n");
	CASE("x zero", "%x", 0);
	CASE("x small", "%x", 255);
	CASE("x max", "%x", UINT_MAX);
	CASE("X small", "%X", 255);
	CASE("X deadbeef", "%X", 3735928559u);
}

static void	suite_pointer_mixed(int *stack_addr)
{
	printf("-- %%p   (NULL differs by platform, see notes)\n");
	CASE("p stack address", "%p", (void *)stack_addr);
	CASE("p NULL", "%p", (void *)0);
	CASE("p small value", "%p", (void *)42);
	printf("-- mixed\n");
	CASE("many conversions", "%s|%d|%c|%x|%%", "mix", -7, 'z', 48879);
	CASE("adjacent numbers", "%d%d%d", 1, 2, 3);
	CASE("percent at end", "abc%%");
}

static void	printf_suite(void)
{
	int	x;

	x = 0;
	g_fails = 0;
	g_total = 0;
	printf("== ft_printf vs printf\n");
	suite_basic();
	suite_numbers();
	suite_pointer_mixed(&x);
	printf("\n  %d cases, %d return-value mismatches\n\n", g_total, g_fails);
}

#else

static void	printf_suite(void)
{
	printf("== ft_printf suite skipped\n");
	printf("   rebuild with -D USE_FT_PRINTF and link libftprintf.a\n\n");
}

#endif

/* ------------------------------------------------------------------ */

int	main(int argc, char **argv)
{
	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'p')
	{
		printf_suite();
		return (0);
	}
	if (argc == 2 && argv[1][0] == '-' && argv[1][1] == '\0')
	{
		PF("== stdin\n");
		drain(0);
		return (0);
	}
	if (argc == 2)
	{
		run_case(argv[1], argv[1], -1);
		return (0);
	}
	gnl_suite();
	sync_out();
	printf_suite();
	return (0);
}
