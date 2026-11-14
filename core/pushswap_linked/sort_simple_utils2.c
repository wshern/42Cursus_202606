/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 15:40:10 by werlim            #+#    #+#             */
/*   Updated: 2026/11/09 15:42:04 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	break_counter(t_node *a)
{
	t_node	*node;
	int		breaks;

	node = a;
	breaks = 0;
	while (node && node->next)
	{
		if (node->rank > node->next->rank)
			breaks++;
		node = node->next;
	}
	if (node && node->rank > a->rank)
		breaks++;
	return (breaks);
}

static int	find_min_rank_position(t_node *a)
{
	int	position;

	position = 0;
	while (a && a->rank != 0)
	{
		position++;
		a = a->next;
	}
	return (position);
}

static void	rotate_sort_fast(t_ps *ps, int position)
{
	int	count;

	if (position <= ps->size_a - position)
	{
		count = position;
		while (count-- > 0)
			op_ra(ps);
	}
	else
	{
		count = ps->size_a - position;
		while (count-- > 0)
			op_rra(ps);
	}
}

int	try_rotation_sorting(t_ps *ps)
{
	int	breaks;
	int	position;

	if (!ps->a || ps->size_a <= 1)
		return (1);
	breaks = break_counter(ps->a);
	if (breaks == 0)
		return (1);
	if (breaks != 1)
		return (0);
	position = find_min_rank_position(ps->a);
	rotate_sort_fast(ps, position);
	return (1);
}
