/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:38:10 by ukperei           #+#    #+#             */
/*   Updated: 2026/10/22 18:43:34 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	move_mrank_top(t_ps *ps)
{
	int	position;
	int	count;

	position = find_mrank_position(ps->b);
	if (position <= ps->size_b / 2)
	{
		while (position > 0)
		{
			op_rb(ps);
			position--;
		}
	}
	else
	{
		count = ps->size_b - position;
		while (count > 0)
		{
			op_rrb(ps);
			count--;
		}
	}
}

void	push_sorted_b(t_ps *ps)
{
	while (ps->size_b > 0)
	{
		move_mrank_top(ps);
		op_pa(ps);
	}
}
