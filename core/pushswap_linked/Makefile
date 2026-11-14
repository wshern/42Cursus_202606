# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/27 00:41:53 by werlim            #+#    #+#              #
#    Updated: 2026/11/13 18:26:59 by werlim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME	= 	push_swap
# CC		=	cc
# CFLAGS	=	-Wall -Wextra -Werror

# LIBFT_DIR	=	libft
# LIBFT		=	$(LIBFT_DIR)/libft.a
# PRINTF_DIR	=	ps_printf
# PRINTF		=	$(PRINTF_DIR)/libpsprintf.a

# INCLUDES	=	-I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)

# SRCS		=	main.c\
# 				op_push.c op_swap.c op_rotate.c op_rev_rotate.c\
# 				parsing.c parsing_utils.c parsing_utils2.c\
# 				ps_assign_rank.c ps_assign_flag.c\
# 				ps_bench.c ps_disorder.c ps_dispatch.c\
# 				ps_is_sorted.c ps_node_utils.c ps_struct_init.c\
# 				sort_simple.c sort_simple2.c\
# 				sort_simple_utils.c sort_simple_utils2.c\
# 				sort_medium.c sort_medium_utils.c sort_medium_utils2.c\
# 				sort_complex.c sort_adaptive.c

# OBJS	=	$(SRCS:.c=.o)

# all: libs $(NAME)

# libs:
# 	$(MAKE) -C $(LIBFT_DIR)
# 	$(MAKE) -C $(PRINTF_DIR)
	
# $(NAME): libs $(OBJS) $(LIBFT) $(PRINTF)
# 	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lpsprintf -o $(NAME)

# %.o: %.c push_swap.h
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# clean:
# 	$(MAKE) -C $(LIBFT_DIR) clean
# 	$(MAKE) -C $(PRINTF_DIR) clean
# 	rm -f $(OBJS)

# fclean: clean
# 	$(MAKE) -C $(LIBFT_DIR) fclean
# 	$(MAKE) -C $(PRINTF_DIR) fclean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all libs clean fclean re


NAME		=	push_swap
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

LIBFT_DIR	=	libft
LIBFT		=	$(LIBFT_DIR)/libft.a
PRINTF_DIR	=	ps_printf
PRINTF		=	$(PRINTF_DIR)/libpsprintf.a

INCLUDES	=	-I. -I$(LIBFT_DIR) -I$(PRINTF_DIR)

SRCS		=	main.c\
				op_push.c op_swap.c op_rotate.c op_rev_rotate.c\
				parsing.c parsing_utils.c parsing_utils2.c\
				ps_assign_rank.c ps_assign_flag.c\
				ps_bench.c ps_disorder.c ps_dispatch.c\
				ps_is_sorted.c ps_node_utils.c ps_struct_init.c\
				sort_simple.c sort_simple2.c\
				sort_simple_utils.c sort_simple_utils2.c\
				sort_medium.c sort_medium_utils.c sort_medium_utils2.c\
				sort_complex.c sort_adaptive.c

OBJS		=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lpsprintf -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
