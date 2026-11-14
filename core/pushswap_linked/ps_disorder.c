/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_disorder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 17:28:04 by werlim            #+#    #+#             */
/*   Updated: 2026/10/16 18:49:21 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double	calc_disorder(t_node *node)
{
	t_node	*t1;
	t_node	*t2;
	long	mistake;
	long	total_pairs;

	if (!node || !node->next)
		return (0);
	t1 = node;
	mistake = 0;
	total_pairs = 0;
	while (t1 != NULL)
	{
		t2 = t1->next;
		while (t2 != NULL)
		{
			total_pairs += 1;
			if (t1->rank > t2->rank)
				mistake++;
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	return ((double)mistake / total_pairs);
}
