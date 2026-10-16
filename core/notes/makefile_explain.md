# push_swap Makefiles: eval cheat sheet

Two Makefiles:

| file | builds | kind |
|---|---|---|
| `Makefile` (root) | `push_swap` | **program** Makefile |
| `ps_printf/Makefile` | `libpsprintf.a` | **library** Makefile |

The root Makefile first asks `ps_printf/Makefile` to build the library, then compiles push_swap and **links** the library into the final program.

```
make
 │
 ├─ libs ──► make -C ps_printf ──► ps_printf.o ps_putchar.o ps_putstr.o ps_putnbr.o
 │                                        │
 │                                        └─ ar rcs ──► libpsprintf.a
 │
 └─ $(NAME) ──► main.o op_push.o … sort_complex.o
                      │
                      └─ cc … -Lps_printf -lpsprintf ──► push_swap
```

---

## 1. How make thinks

A **rule** has three parts:

```
target: prerequisites
<TAB>recipe (shell command)
```

- **target**: the file to produce (e.g. `push_swap`).
- **prerequisites**: what the target is built from (e.g. the `.o` files).
- **recipe**: the command that builds it. It **must** start with a TAB character, not spaces.

make compares **modification times**. It runs a recipe only if the target is missing, or if some prerequisite is newer than the target. Otherwise it prints "Nothing to be done". That's how both Makefiles avoid relinking and recompiling.

---

## 2. Library Makefile (`ps_printf/Makefile`)

```make
NAME   = libpsprintf.a
CC     = cc
CFLAGS = -Wall -Wextra -Werror
SRCS   = ps_printf.c ps_putchar.c ps_putstr.c ps_putnbr.c
OBJS   = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ps_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```

What each part does:

- **`$(OBJS)`**: compile each `.c` into a `.o` (object file: machine code, not yet runnable).
- **`ar rcs`**: pack the `.o` files into **one archive**, `libpsprintf.a`. A static library is just a bundle of object files.
- **Why `lib` in the name**: the linker flag `-lpsprintf` searches for a file named `lib` + `psprintf` + `.a`. Without the `lib` prefix, `-l` can't find it.
- **No `main`, no linking**: a library is never run on its own. It's only material for a program.

---

## 3. Program Makefile (root `Makefile`)

```make
NAME       = push_swap
CC         = cc
CFLAGS     = -Wall -Wextra -Werror

PRINTF_DIR = ps_printf
PRINTF     = $(PRINTF_DIR)/libpsprintf.a
INCLUDES   = -I. -I$(PRINTF_DIR)

SRCS = main.c \
       op_push.c op_swap.c … sort_simple_utils.c
OBJS = $(SRCS:.c=.o)

all: libs $(NAME)

libs:
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJS) $(PRINTF)
	$(CC) $(CFLAGS) $(OBJS) -L$(PRINTF_DIR) -lpsprintf -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all libs clean fclean re
```

What each part does:

- **`all: libs $(NAME)`**: build the library first, then the program.
- **`libs`**: runs the library's own Makefile (`make -C ps_printf`). The library builds itself, using its own rules.
- **`$(NAME)`**: **links** all push_swap `.o` files together with `libpsprintf.a` into the runnable `push_swap`.
- **`clean` / `fclean`**: clean push_swap's files **and** forward the request to the library's Makefile.

---

## 4. Program vs library Makefile

| | library (`ps_printf`) | program (`push_swap`) |
|---|---|---|
| output | `libpsprintf.a`, an archive of `.o` files | `push_swap`, a runnable executable |
| final step | `ar rcs` (pack) | `cc … -o push_swap` (**link**) |
| contains `main`? | no | yes (`main.c`) |
| can you run it? | no | yes |
| depends on other Makefiles? | no, it's self-contained | yes, it calls `make -C ps_printf` |
| header dependency | `ps_printf.h` | `push_swap.h` |
| `-I` needed? | no, its header is in the same folder | yes, `-I.` and `-Ips_printf` |
| `-L` / `-l` needed? | no | yes, to link the library |

---

## 5. Symbols and syntax

### Variables

| syntax | meaning | example |
|---|---|---|
| `NAME = value` | define a variable | `CC = cc` |
| `$(NAME)` | use the variable (text substitution) | `$(CC)` → `cc` |
| `$(SRCS:.c=.o)` | substitution reference: replace `.c` with `.o` in every word | `main.c op_push.c` → `main.o op_push.o` |
| `\` at end of line | continue on the next line (one long value) | the `SRCS` list |

### Automatic variables (only valid inside a recipe)

| symbol | means | in `%.o: %.c push_swap.h`, compiling `op_push.o` |
|---|---|---|
| `$@` | the target | `op_push.o` |
| `$<` | the **first** prerequisite | `op_push.c` |
| `$^` | all prerequisites | `op_push.c push_swap.h` (not used here) |

### Rules

| syntax | meaning |
|---|---|
| `%.o: %.c push_swap.h` | **pattern rule**: any `X.o` is built from `X.c`. `%` matches the same stem on both sides. |
| `.PHONY: all clean …` | these targets are **names of actions, not files**. Without it, a file called `clean` in the folder would make `make clean` say "up to date" and do nothing. |
| `$(MAKE)` | the make program itself. Use it instead of the literal word `make`, so flags pass through. |
| `-C dir` | run make **inside** `dir`, using that folder's Makefile |
| `re: fclean all` | rebuild from scratch: run `fclean`, then `all` |

### Compiler and archiver flags

| flag | meaning |
|---|---|
| `-Wall -Wextra -Werror` | enable warnings, extra warnings, and turn every warning into an error (required by 42) |
| `-c` | compile only: produce a `.o`, don't link |
| `-o file` | name of the output file |
| `-I dir` | where to search for `#include "…"` headers |
| `-L dir` | where to search for libraries when linking |
| `-lname` | link the library `libname.a` (so `-lpsprintf` → `libpsprintf.a`) |
| `ar rcs` | `r` insert/replace the `.o` files, `c` create the archive if missing, `s` write an index so the linker can find functions quickly |

---

## 6. Likely eval questions

**"Show me it doesn't relink."**
Run `make` twice. The second run prints "Nothing to be done" for the library and nothing for `push_swap`. `libs` always runs, because it's phony, but the library's own Makefile finds nothing newer and doesn't touch `libpsprintf.a`. So `push_swap`'s prerequisites are unchanged, and it isn't linked again.

**"Why is `libs` a separate rule and not a prerequisite of `push_swap`?"**
A phony target is always considered out of date. If `push_swap` depended directly on `libs`, it would relink on **every** `make`. Keeping `libs` in `all` and making `push_swap` depend on the **file** `libpsprintf.a` means it relinks only when the library really changed.

**"What happens if I edit `push_swap.h`?"**
Every push_swap `.o` is rebuilt, because the pattern rule lists `push_swap.h` as a prerequisite. A changed struct layout must reach every file that uses it.

**"What happens if I edit one `.c`?"**
Only that `.o` is recompiled, and then `push_swap` is relinked.

**"Difference between `clean` and `fclean`?"**
`clean` removes the object files (`.o`), in both folders. `fclean` also removes the final products: `push_swap` and `libpsprintf.a`.

**"Why a static library at all?"**
`ps_printf` is a separate, reusable piece with its own build. Packing it as `libpsprintf.a` keeps push_swap's Makefile simple, because it links one file instead of compiling printf's sources itself.

---

## 7. Two honest limitations (if asked)

- **The push_swap objects don't list `ps_printf.h` as a prerequisite.** If only `ps_printf.h` changes (for example a new prototype), push_swap's `.o` files aren't recompiled. `make re` fixes it.
- **Parallel builds (`make -j`):** `libs` and the push_swap objects could build at the same time, and linking might start before `libpsprintf.a` exists. A normal `make` runs left to right (`libs` first), so it's correct for how the project is built and evaluated.