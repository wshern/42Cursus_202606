/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:38:10 by ukperei           #+#    #+#             */
/*   Updated: 2026/10/22 18:43:34 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_chunk_size(int size)
{
	int	chunk;

	chunk = 1;
	while (chunk * chunk < size)
		chunk++;
	return (chunk);
}

int	in_chunk(t_node *node, int start, int end)
{
	if (node->rank >= start && node->rank < end)
		return (1);
	return (0);
}

int	chunk_remainder(t_node *a, int start, int end)
{
	while (a)
	{
		if (a->rank >= start && a->rank < end)
			return (1);
		a = a->next;
	}
	return (0);
}

int	find_mrank_position(t_node *b)
{
	int	max;
	int	position;
	int	max_position;

	max = b->rank;
	position = 0;
	max_position = 0;
	while (b)
	{
		if (b->rank > max)
		{
			max = b->rank;
			max_position = position;
		}
		position++;
		b = b->next;
	}
	return (max_position);
}

/*
int	find_mrank_b(t_node *b)
{
	int	max;

	max = b->rank;
	while (b)
	{
		if (b->rank > max)
			max = b->rank;
		b = b->next;
	}
	return (max);
}*/