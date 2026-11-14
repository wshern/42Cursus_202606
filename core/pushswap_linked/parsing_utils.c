/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:38:10 by lukperei          #+#    #+#             */
/*   Updated: 2026/11/10 21:29:26 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_split(char **numbers)
{
	int	i;

	i = 0;
	while (numbers[i])
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	has_duplicate(t_node *a, int value)
{
	while (a)
	{
		if (a->data == value)
			return (1);
		a = a->next;
	}
	return (0);
}
