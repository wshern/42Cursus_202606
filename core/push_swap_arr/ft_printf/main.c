/* main.c -- ft_printf tester
 *
 * Compares your ft_printf against the real printf, automatically,
 * on both the printed BYTES and the RETURN VALUE.
 *
 * build:
 *   cc -Wall -Wextra -Werror main.c libftprintf.a -o pf
 *   ./pf
 *
 * If your header or library sits elsewhere:
 *   cc -Wall -Wextra -Werror -I../ft_printf main.c \
 *      ../ft_printf/libftprintf.a -o pf
 *
 * Exit status is 0 when every case passes, 1 otherwise, so this can
 * go straight into a shell loop.
 */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#define CAPBUF 8192

static int	g_total;
static int	g_fails;
static int	g_saved;
static int	g_pipe[2];

/* gcc checks literal format strings at compile time and rejects a
 * literal NULL argument to %s under -Werror. volatile stops it from
 * folding the value, so the case still runs. */
static char *volatile	g_nullstr = NULL;

/* ------------------------------------------------------------------ */
/* capturing stdout                                                    */
/* ------------------------------------------------------------------ */

/* Point fd 1 at a pipe so everything printed lands in a buffer we can
 * inspect instead of on the terminal. ft_printf writes to fd 1 with
 * write(); printf writes to fd 1 through its own buffer. Redirecting
 * the descriptor catches both. */
static void	cap_start(void)
{
	fflush(stdout);
	g_saved = dup(1);
	if (pipe(g_pipe) == -1)
		return ;
	dup2(g_pipe[1], 1);
	close(g_pipe[1]);
}

/* Restore fd 1, then drain the pipe. The flush matters: printf may
 * still be holding bytes, and they must reach the pipe before fd 1
 * points back at the terminal. Returns the byte count, which is what
 * gets compared -- not strlen, because a case may legitimately print
 * an embedded '\0'. */
static int	cap_stop(char *buf, int size)
{
	int	n;

	fflush(stdout);
	dup2(g_saved, 1);
	close(g_saved);
	n = read(g_pipe[0], buf, size - 1);
	close(g_pipe[0]);
	if (n < 0)
		n = 0;
	buf[n] = '\0';
	return (n);
}

/* ------------------------------------------------------------------ */
/* reporting                                                           */
/* ------------------------------------------------------------------ */

/* Show bytes with nothing hidden: a NUL, a newline or a high byte is
 * printed as an escape rather than sent to the terminal raw. */
static void	show_bytes(const char *buf, int len)
{
	int				i;
	unsigned char	c;

	i = 0;
	while (i < len)
	{
		c = (unsigned char)buf[i];
		if (c == '\0')
			printf("\\0");
		else if (c == '\n')
			printf("\\n");
		else if (c < 32 || c > 126)
			printf("\\x%02x", c);
		else
			printf("%c", c);
		i++;
	}
}

static void	report(const char *label, const char *ft, int ft_len, int ft_ret,
			const char *std, int std_len, int std_ret)
{
	int	text_ok;
	int	ret_ok;

	text_ok = (ft_len == std_len && memcmp(ft, std, ft_len) == 0);
	ret_ok = (ft_ret == std_ret);
	g_total++;
	if (text_ok && ret_ok)
	{
		printf("  ok   %-22s ", label);
		show_bytes(std, std_len);
		printf("  (ret %d)\n", std_ret);
		return ;
	}
	g_fails++;
	printf("  FAIL %-22s\n", label);
	printf("         ft  [");
	show_bytes(ft, ft_len);
	printf("] ret %d\n", ft_ret);
	printf("         std [");
	show_bytes(std, std_len);
	printf("] ret %d\n", std_ret);
	if (!text_ok && !ret_ok)
		printf("         text and return value differ\n");
	else if (!text_ok)
		printf("         text differs (%d bytes vs %d)\n", ft_len, std_len);
	else
		printf("         return value differs\n");
}

/* The call has to happen inside the macro. ft_printf takes "..." and
 * there is no way to forward a va_list into it, so the two calls are
 * expanded twice here rather than passed to a helper. */
#define CASE(label, ...)                                              \
	do {                                                              \
		static char	ft_buf[CAPBUF];                                   \
		static char	std_buf[CAPBUF];                                  \
		int			ft_len;                                           \
		int			std_len;                                          \
		int			ft_ret;                                           \
		int			std_ret;                                          \
		cap_start();                                                  \
		ft_ret = ft_printf(__VA_ARGS__);                              \
		ft_len = cap_stop(ft_buf, CAPBUF);                            \
		cap_start();                                                  \
		std_ret = printf(__VA_ARGS__);                                \
		std_len = cap_stop(std_buf, CAPBUF);                          \
		report(label, ft_buf, ft_len, ft_ret,                         \
			std_buf, std_len, std_ret);                               \
	} while (0)

/* ------------------------------------------------------------------ */
/* the cases                                                           */
/* ------------------------------------------------------------------ */

/* printf("") cannot go through CASE: gcc rejects a zero-length literal
 * format under -Werror. ft_printf is not format-checked, so it is
 * called directly and compared against printf's known answer for an
 * empty format -- no bytes, return 0. */
static void	case_empty_format(void)
{
	static char	buf[CAPBUF];
	int			len;
	int			ret;

	cap_start();
	ret = ft_printf("");
	len = cap_stop(buf, CAPBUF);
	report("empty format", buf, len, ret, "", 0, 0);
}

static void	suite_literal(void)
{
	printf("-- literal text and %%%%\n");
	CASE("plain", "hello");
	case_empty_format();
	CASE("newline", "a\nb");
	CASE("single percent", "100%%");
	CASE("two percents", "%%%%");
	CASE("percent then text", "%%abc");
	CASE("text then percent", "abc%%");
}

static void	suite_char_str(void)
{
	printf("-- %%c\n");
	CASE("c letter", "%c", 'A');
	CASE("c digit", "%c", '0');
	CASE("c space", "%c", ' ');
	CASE("c null byte", "%c", '\0');
	CASE("c high byte", "%c", (char)200);
	CASE("c tab", "%c", '\t');
	printf("-- %%s\n");
	CASE("s normal", "%s", "forty two");
	CASE("s empty", "%s", "");
	CASE("s NULL", "%s", g_nullstr);
	CASE("s with percent", "%s", "50%");
	CASE("s with newline", "%s", "a\nb");
	CASE("s long", "%s",
		"0123456789012345678901234567890123456789012345678901234567890123");
}

static void	suite_signed(void)
{
	printf("-- %%d and %%i\n");
	CASE("d zero", "%d", 0);
	CASE("d one digit", "%d", 7);
	CASE("d positive", "%d", 42);
	CASE("d negative", "%d", -42);
	CASE("d minus one", "%d", -1);
	CASE("d INT_MAX", "%d", INT_MAX);
	CASE("d INT_MIN", "%d", INT_MIN);
	CASE("i zero", "%i", 0);
	CASE("i negative", "%i", -2147483647);
	CASE("i INT_MIN", "%i", INT_MIN);
}

static void	suite_unsigned(void)
{
	printf("-- %%u\n");
	CASE("u zero", "%u", 0u);
	CASE("u small", "%u", 42u);
	CASE("u INT_MAX", "%u", (unsigned int)INT_MAX);
	CASE("u UINT_MAX", "%u", UINT_MAX);
	CASE("u from -1", "%u", (unsigned int)-1);
	CASE("u from INT_MIN", "%u", (unsigned int)INT_MIN);
}

static void	suite_hex(void)
{
	printf("-- %%x and %%X\n");
	CASE("x zero", "%x", 0u);
	CASE("x nine", "%x", 9u);
	CASE("x ten", "%x", 10u);
	CASE("x fifteen", "%x", 15u);
	CASE("x sixteen", "%x", 16u);
	CASE("x 255", "%x", 255u);
	CASE("x UINT_MAX", "%x", UINT_MAX);
	CASE("X zero", "%X", 0u);
	CASE("X ten", "%X", 10u);
	CASE("X 255", "%X", 255u);
	CASE("X deadbeef", "%X", 3735928559u);
	CASE("X UINT_MAX", "%X", UINT_MAX);
}

static void	suite_pointer(int *stack_addr, char *heap_like)
{
	printf("-- %%p   (NULL output differs by platform)\n");
	CASE("p stack address", "%p", (void *)stack_addr);
	CASE("p string literal", "%p", (void *)heap_like);
	CASE("p NULL", "%p", (void *)0);
	CASE("p value 1", "%p", (void *)1);
	CASE("p value 42", "%p", (void *)42);
	CASE("p large", "%p", (void *)0x7fffffffffff);
}

static void	suite_mixed(void)
{
	printf("-- several conversions in one call\n");
	CASE("all of them", "%c %s %p %d %i %u %x %X %%",
		'z', "str", (void *)0x1234, -5, 5, 5u, 255u, 255u);
	CASE("adjacent", "%d%d%d", 1, 2, 3);
	CASE("no spaces", "%s%s%s", "a", "b", "c");
	CASE("around text", "start %d middle %s end", 7, "x");
	CASE("repeated same", "%x %x %x", 1u, 255u, 4096u);
	CASE("null string mixed", "[%s] [%d]", g_nullstr, 0);
}

/* A format string ending in a lone '%' is undefined behaviour in the
 * standard. It is left out on purpose: whatever printf does with it
 * is not a target to match. */
static void	suite_stress(void)
{
	int	i;

	printf("-- repetition\n");
	i = 0;
	while (i < 3)
	{
		CASE("loop d", "%d", i * 1000);
		i++;
	}
}

/* ------------------------------------------------------------------ */

int	main(void)
{
	int		x;
	char	*lit;

	x = 0;
	lit = "anchor";
	g_total = 0;
	g_fails = 0;
	printf("ft_printf vs printf\n\n");
	suite_literal();
	suite_char_str();
	suite_signed();
	suite_unsigned();
	suite_hex();
	suite_pointer(&x, lit);
	suite_mixed();
	suite_stress();
	printf("\n%d cases, %d failed\n", g_total, g_fails);
	if (g_fails)
		return (1);
	return (0);
}
