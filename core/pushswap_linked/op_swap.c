/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 17:00:50 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:37:24 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	op_swap(t_node **node)
{
	t_node	*first;
	t_node	*second;
	t_node	*third;

	if (!node || !*node || !(*node)->next)
		return ;
	first = *node;
	second = (*node)->next;
	third = (*node)->next->next;
	second->next = first;
	first->next = third;
	*node = second;
}

void	op_sa(t_ps *ps)
{
	op_swap(&ps->a);
	ps->counter[OP_SA]++;
	ps_printf(1, "sa\n");
}

void	op_sb(t_ps *ps)
{
	op_swap(&ps->b);
	ps->counter[OP_SB]++;
	ps_printf(1, "sb\n");
}

void	op_ss(t_ps *ps)
{
	op_swap(&ps->a);
	op_swap(&ps->b);
	ps->counter[OP_SS]++;
	ps_printf(1, "ss\n");
}
