/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/26 02:42:43 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:37:10 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	op_push(t_node **src, t_node **dest)
{
	t_node	*temp;

	if (!src || !*src)
		return (0);
	temp = (*src)->next;
	(*src)->next = *dest;
	*dest = *src;
	*src = temp;
	return (1);
}

void	op_pa(t_ps *ps)
{
	int	num;

	num = op_push(&ps->b, &ps->a);
	ps->size_a += num;
	ps->size_b -= num;
	ps->counter[OP_PA]++;
	ps_printf(1, "pa\n");
}

void	op_pb(t_ps *ps)
{
	int	num;

	num = op_push(&ps->a, &ps->b);
	ps->size_b += num;
	ps->size_a -= num;
	ps->counter[OP_PB]++;
	ps_printf(1, "pb\n");
}
