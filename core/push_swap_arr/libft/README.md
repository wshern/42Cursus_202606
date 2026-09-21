*This project has been created as part of the 42 curriculum by werlim.*

# libft

## Description

libft is a static C library that reimplements a selection of C standard library
functions from scratch, plus a set of additional utilities and a singly linked list
implementation. No standard library equivalent is called; only `malloc`, `free` and
`write` are used.

The goal is to understand how these functions actually work: string traversal,
manual memory allocation, and who owns allocated memory once a function returns, and
linked list.
The resulting `libft.a` is reused as a dependency throughout the rest of the
cursus.

## Instructions

    make        - compiles libft.a
    make clean  - removes object files
    make fclean - removes object files and libft.a
    make re     - fclean then make

Compiled with `cc -Wall -Wextra -Werror`. Norm checked with Norm 4.1.

To use in another project:

    #include "libft.h"

    cc main.c libft.a -I.

## Resources

- The libft and Norm subject PDFs.
- The man pages for every reimplemented function, used as the specification for
  return values and edge case behaviour.

### Use of AI

An AI assistant was used as a tutor, under a standing rule that it would
not write implementation code. Its use was limited to:

- Explaining new concepts: pointer arithmetic, pointers to pointers, function
  pointers, linked list structure.
- Breaking down coomplicated explanations from sources like man pages.
- Showing unfamiliar syntax in generic form only, never as part of a project
  function (for example `->` and function pointer declarations).

Every function was written by hand and every bug located are fixed by hand.

## Library description

### Part 1 - included functions

Character check and manipulation:
- ft_isalpha
- ft_isdigit
- ft_isalnum
- ft_isascii
- ft_isprint
- ft_toupper
- ft_tolower

String manipulation:
- ft_strlen
- ft_strlcpy
- ft_strlcat
- ft_strchr
- ft_strrchr
- ft_strncmp
- ft_strnstr
- ft_substr
- ft_strjoin
- ft_strtrim
- ft_split
- ft_strmapi
- ft_striteri

Memory manipulation:
- ft_calloc
- ft_memset
- ft_bzero
- ft_memcpy
- ft_memmove
- ft_memchr
- ft_memcmp
- ft_strdup

Number handling:
- ft_atoi
- ft_itoa

Writing to a file descriptor:
- ft_putchar_fd
- ft_putstr_fd
- ft_putendl_fd
- ft_putnbr_fd

List manipulation:
- ft_lstnew
- ft_lstadd_front
- ft_lstsize
- ft_lstlast
- ft_lstadd_back
- ft_lstdelone
- ft_lstclear
- ft_lstiter
- ft_lstmap
