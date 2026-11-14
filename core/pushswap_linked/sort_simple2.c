/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/09 15:38:21 by werlim            #+#    #+#             */
/*   Updated: 2026/11/09 15:38:30 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_simple_all(t_ps *ps)
{
	while (ps->size_a > 0)
	{
		move_min_top(ps);
		op_pb(ps);
	}
	while (ps->size_b > 0)
		op_pa(ps);
}

void	sort_two(t_ps *ps)
{
	if (ps->a->rank > ps->a->next->rank)
		op_sa(ps);
}

void	sort_three(t_ps *ps)
{
	int	max;

	max = find_max(ps->a);
	if (ps->a->rank == max)
		op_ra(ps);
	else if (ps->a->next->rank == max)
		op_rra(ps);
	if (ps->a->rank > ps->a->next->rank)
		op_sa(ps);
}

void	sort_four(t_ps *ps)
{
	move_min_top(ps);
	op_pb(ps);
	sort_three(ps);
	op_pa(ps);
}

void	sort_five(t_ps *ps)
{
	move_min_top(ps);
	op_pb(ps);
	move_min_top(ps);
	op_pb(ps);
	sort_three(ps);
	op_pa(ps);
	op_pa(ps);
}
