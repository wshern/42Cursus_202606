/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_is_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/07 21:21:10 by werlim            #+#    #+#             */
/*   Updated: 2026/10/22 19:39:40 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// neighbour comparison method
// 1 = empty list/sorted 
// 0 = not sorted
int	ps_is_sorted(t_node *node)
{
	if (!node)
		return (1);
	while (node->next != NULL)
	{
		if (node->rank < node->next->rank)
			node = node->next;
		else
			return (0);
	}
	return (1);
}

// int comparison method
// int is_sorted(t_node *node)
// {
// 	int i;

// 	if (!node)
// 		return (1);
// 	i = 0;
// 	while (node->next != NULL)
// 	{
// 		if (node->rank != i)
// 			return (0);
// 		node = node->next;
// 		i++;
// 	}
// 	return (1);
// }
