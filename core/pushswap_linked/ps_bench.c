/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 11:10:15 by werlim            #+#    #+#             */
/*   Updated: 2026/10/15 15:10:37 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static const char	*tbl_strat(int ref)
{
	const char	*strategy[4];

	strategy[0] = "Simple";
	strategy[1] = "Medium";
	strategy[2] = "Complex";
	strategy[3] = "Adaptive";
	return (strategy[ref]);
}

static const char	*tbl_class(int ref)
{
	const char	*class[3];

	class[0] = "O(n²)";
	class[1] = "O(n√n)";
	class[2] = "O(n log n)";
	return (class[ref]);
}

void	bench(t_ps *ps)
{
	double	disorder;
	int		total_ops;
	int		i;

	disorder = ps->disorder * 100;
	total_ops = 0;
	i = 0;
	while (i < OP_NUM)
		total_ops += ps->counter[i++];
	ps_printf(2, "[bench]  disorder:    %f%%\n", disorder);
	ps_printf(2, "[bench]  strategy:    %s / %s\n", tbl_strat(ps->type_strat),
		tbl_class(ps->type_class));
	ps_printf(2, "[bench]  total_ops:  %d\n", total_ops);
	ps_printf(2, "[bench]  sa:  %d  sb:  %d  ss:  %d  pa:  %d  pb:  %d\n",
		ps->counter[OP_SA], ps->counter[OP_SB], ps->counter[OP_SS],
		ps->counter[OP_PA], ps->counter[OP_PB]);
	ps_printf(2, "[bench]  ra:  %d  rb:  %d  rr:  %d  ",
		ps->counter[OP_RA], ps->counter[OP_RB], ps->counter[OP_RR]);
	ps_printf(2, "rra:  %d  rrb:  %d  rrr:  %d\n",
		ps->counter[OP_RRA], ps->counter[OP_RRB], ps->counter[OP_RRR]);
}
