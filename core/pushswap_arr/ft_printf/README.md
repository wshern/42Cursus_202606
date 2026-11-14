*This project has been created as part of the 42 curriculum by werlim.*

# ft_printf

## Description

ft_printf reimplements a subset of `printf()`. It takes a format string and a
variable number of arguments, writes the formatted result to standard output,
and returns the number of bytes written.

| Specifier | Prints                                                  |
|-----------|---------------------------------------------------------|
| `%c`      | a single character                                       |
| `%s`      | a string, or `(null)` if the pointer is NULL             |
| `%p`      | a pointer as `0x` + lowercase hex, or `(nil)`            |
| `%d` `%i` | a signed decimal integer                                 |
| `%u`      | an unsigned decimal integer                              |
| `%x` `%X` | an unsigned integer in lower/uppercase hexadecimal       |
| `%%`      | a literal percent sign                                   |

Width, precision and flags are bonus and are not implemented.

Where the C standard leaves behaviour to the implementation, this project
follows glibc, since grading is done on Linux. Hence `(null)` for a NULL `%s`
and `(nil)` for a NULL `%p`. No buffering: every character is sent to fd 1 with
`write()` as soon as it is produced.

## Instructions

```
make            build libftprintf.a
make clean      remove object files
make fclean     remove object files and the library
make re         rebuild from scratch
```

```c
#include "ft_printf.h"

int main(void)
{
    int count;

    count = ft_printf("Hello %s, you are %d years old\n", "world", 42);
    ft_printf("that call printed %d bytes\n", count);
    return (0);
}
```

```
cc -Wall -Wextra -Werror main.c -L. -lftprintf -o program
```

The subject authorises `write`, `malloc`, `free` and the `va_` macros. This
implementation uses only `write` and the `va_` macros, so it allocates nothing
and cannot leak.

## Algorithm and data structures

### Structure

```
ft_printf          creates the va_list, returns the total byte count
    |
f_passby           walks the format string one character at a time
    |
f_ident            reads one argument, dispatches on the conversion letter
    |
handler_int / handler_unsigned / handler_ptr / ftp_putstr / ftp_putchar
    |
ftp_putnbr         the shared number-to-text engine
```

Each layer has one responsibility and returns the number of bytes it caused to
be written. `ft_printf` is the only function that may call `va_start` and
`va_end`, because those macros are only valid in a function that literally
declares `...`.

### Passing the va_list by address

`f_passby` and `f_ident` take a `va_list *`, not a `va_list`.

A `va_list` is a cursor onto the next unread argument, so it has to be shared —
each conversion must continue where the last stopped. The standard does not say
whether passing one by value gives the callee the original or a copy, and
platforms differ: on x86-64 Linux it is a one-element array type that decays to
a pointer, so the callee updates the caller's cursor; on arm64 macOS it is a
struct, so it is copied and the callee's progress is lost on return. The same
source then prints the first argument repeatedly on one platform and works on
the other. Passing the address removes the ambiguity — every copy of an address
refers to the same cursor — and `va_arg` is applied to `*list`.

### One engine for five specifiers

`%d`, `%i`, `%u`, `%x`, `%X` and the digits of `%p` are the same operation:
express a non-negative magnitude in some base using some set of digit
characters. One recursive function serves them all:

```c
static int ftp_putnbr(unsigned long nbr, int base, const char *alnum);
```

`nbr % base` gives the last digit, `nbr / base` gives the rest. Since that
produces digits in reverse, the function recurses on `nbr / base` before
printing `nbr % base`, so the deepest call emits the most significant digit
first. The base case, `nbr / base == 0`, is also true for zero, so `0` prints
correctly with no special case.

`base` and `alnum` are parameters so the same body serves decimal and both
cases of hex. The remainder indexes into `alnum`; adding `'0'` would not work,
because `a`–`f` are not adjacent to the digits in ASCII. The three digit tables
are `static const char *const` at file scope — file-local and read-only, so
named constants rather than mutable global state.

`unsigned long` is the parameter type because a pointer is eight bytes on
x86-64 while an `unsigned int` is four, so a narrower parameter would truncate
every address passed to `%p`. It is unsigned because the sign is resolved one
layer up in `handler_int`, which prints the minus and passes the magnitude; the
engine contains no sign logic at all.

### INT_MIN

Two's complement is asymmetric: a 32-bit `int` holds `-2147483648` but not
`+2147483648`. Remembering the sign and negating therefore fails for `INT_MIN`,
and signed overflow is undefined, so the result cannot be relied on.
`handler_int` catches `INT_MIN` early and prints `"-2147483648"` directly,
which leaves every remaining negation safe. Widening to `long` before negating
would also work; the literal was chosen as easier to read and defend.

### Byte counting

Every function that produces output returns its byte count and every caller
adds it to its own total, so the count is built on the way back out of the call
chain and no length is ever asserted by hand. A count maintained separately
from the printing will eventually disagree with the real `printf`.

### Data structures

None. Nothing is allocated: the format string is read in place, numbers are
converted through recursion rather than into a buffer, and the only persistent
data is the three constant digit tables.

## Resources

- `man 3 printf` and `man 3 stdarg`.
- The System V AMD64 ABI, for variadic argument layout and why `va_list` is an
  array type on that platform.
- The 42 Norm, version 4.1.

### Use of AI

An AI assistant was used as a tutor throughout, under a standing instruction
not to write any of the assignment code. It was used to explain new concepts
(the `va_` macros, default argument promotion, two's complement asymmetry, the
value-versus-representation distinction, scope and lifetime rules); to review
code I had already written and point out bugs that I missed; to confirm real
`printf` behaviour on edge cases by running it.

All code in this repository was written by me. Where a bug was pointed out, the
correction was mine to work out and to write.