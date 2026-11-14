/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_node_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/24 15:11:50 by werlim            #+#    #+#             */
/*   Updated: 2026/10/16 19:07:46 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ps_ndnew(int data, int rank)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->data = data;
	node->rank = rank;
	node->next = NULL;
	return (node);
}

t_node	*ps_ndlast(t_node *node)
{
	if (!node)
		return (NULL);
	while (node->next != NULL)
		node = node->next;
	return (node);
}

void	ps_ndaddlast(t_node **node, t_node *new)
{
	t_node	*temp;

	if (!node || !new)
		return ;
	if (!*node)
	{
		*node = new;
		return ;
	}
	temp = ps_ndlast(*node);
	temp->next = new;
}

void	ps_ndclear(t_node **node)
{
	t_node	*temp;

	while (*node != NULL)
	{
		temp = (*node)->next;
		free(*node);
		*node = temp;
	}
}
