# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/03 16:58:36 by werlim            #+#    #+#              #
#    Updated: 2026/11/13 18:27:09 by werlim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libpsprintf.a
CC		= cc
CFLAGS	= -Wall -Wextra -Werror


SRCS	= ps_printf.c ps_putchar.c ps_putstr.c ps_putnbr.c

OBJS	= $(SRCS:.c=.o)

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