/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 13:37:21 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:36:59 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "ps_printf/ps_printf.h"
# include "libft/libft.h"

typedef struct s_node
{
	int				data;
	int				rank;
	struct s_node	*next;
}	t_node;

typedef enum e_op
{
	OP_SA,
	OP_SB,
	OP_SS,
	OP_PA,
	OP_PB,
	OP_RA,
	OP_RB,
	OP_RR,
	OP_RRA,
	OP_RRB,
	OP_RRR,
	OP_NUM
}	t_op;

typedef enum e_strat
{
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
	STRAT_ADAPTIVE
}	t_strat;

typedef struct s_ps
{
	t_node	*a;
	t_node	*b;
	int		size_a;
	int		size_b;
	double	disorder;
	int		type_strat;
	int		type_class;
	int		counter[OP_NUM];
	int		bench;
}	t_ps;

/* Setup - Struct initialisation */
void	ps_init(t_ps *ps);

/* Input - Parse */
int		ps_parser(t_ps *ps, int ac, char **av);
int		parse_numbers(t_ps *ps, char *arg);
int		parse_flag(t_ps *ps, char *arg, int *strat_set);
int		is_valid_num(char *str);
int		ps_atoi(const char *str, int *result);
int		has_duplicate(t_node *a, int value);
void	free_split(char **numbers);

/* Setup - Rank Assignment */
void	assign_rank(t_node *node);

/* Setup - Disorder Calculation */
double	calc_disorder(t_node *node);

/* Dispatcher */
void	ps_dispatcher(t_ps *ps);

/* Sort - Simple (Selection(Min)) */
void	sort_simple(t_ps *ps);
void	sort_small_num(t_ps *ps);
void	sort_two(t_ps *ps);
void	sort_three(t_ps *ps);
void	sort_four(t_ps *ps);
void	sort_five(t_ps *ps);
void	sort_simple_all(t_ps *ps);
int		find_max(t_node *a);
int		find_min_position(t_node *a);
void	move_min_top(t_ps *ps);
int		try_rotation_sorting(t_ps *ps);

/* Sort - Medium  (Chunk) */
void	sort_medium(t_ps *ps);
int		get_chunk_size(int size);
int		in_chunk(t_node *node, int start, int end);
int		chunk_remainder(t_node *a, int start, int end);
int		find_mrank_position(t_node *b);
void	move_mrank_top(t_ps *ps);
void	push_sorted_b(t_ps *ps);

/* Sort - Complex (Radix) */
void	sort_complex(t_ps *ps);

/* Sort - Adaptive */
void	sort_adaptive(t_ps *ps);

/* Sort Checker (not bonus) */
int		ps_is_sorted(t_node *node);

/* Operations - Swap */
void	op_sa(t_ps *ps);
void	op_sb(t_ps *ps);
void	op_ss(t_ps *ps);

/* Operations - Push */
void	op_pa(t_ps *ps);
void	op_pb(t_ps *ps);

/* Operations - Rotate */
void	op_ra(t_ps *ps);
void	op_rb(t_ps *ps);
void	op_rr(t_ps *ps);
void	op_rra(t_ps *ps);
void	op_rrb(t_ps *ps);
void	op_rrr(t_ps *ps);

/* Bench (--bench) */
void	bench(t_ps *ps);

/* Helper Functions - Node */
t_node	*ps_ndnew(int data, int rank);
t_node	*ps_ndlast(t_node *node);
void	ps_ndaddlast(t_node **node, t_node *new);
void	ps_ndclear(t_node **node);

#endif