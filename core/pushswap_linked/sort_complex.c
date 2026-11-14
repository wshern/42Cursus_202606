/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_complex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 17:14:22 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:57:42 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	radix_algo(t_ps *ps, int divide)
{
	int	n;

	n = ps->size_a;
	while (n != 0)
	{
		if ((ps->a->rank / divide) % 2 == 0)
			op_pb(ps);
		else if ((ps->a->rank / divide) % 2 == 1)
			op_ra(ps);
		n--;
	}
	while (ps->size_b != 0)
		op_pa(ps);
}

void	sort_complex(t_ps *ps)
{
	int	divide;
	int	rank_max;

	ps->type_class = STRAT_COMPLEX;
	if (try_rotation_sorting(ps))
		return ;
	if (ps->size_a < 6)
	{
		sort_small_num(ps);
		return ;
	}
	divide = 1;
	rank_max = ps->size_a - 1;
	while (ps_is_sorted(ps->a) == 0 && rank_max / divide > 0)
	{
		radix_algo(ps, divide);
		divide *= 2;
	}
}
