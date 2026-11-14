/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_rank.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 15:28:38 by werlim            #+#    #+#             */
/*   Updated: 2026/10/12 15:53:00 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_rank(t_node *node)
{
	t_node	*temp;
	t_node	*head;
	int		counter;

	head = node;
	while (node != NULL)
	{
		temp = head;
		counter = 0;
		while (temp != NULL)
		{
			if (node->data > temp->data)
				counter++;
			temp = temp->next;
		}
		node->rank = counter;
		node = node->next;
	}
}
