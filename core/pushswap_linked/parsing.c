/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 14:38:10 by lukperei          #+#    #+#             */
/*   Updated: 2026/11/10 21:48:19 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	validate_one_number(t_ps *ps, char *str)
{
	t_node	*new_node;
	int		value;

	if (!is_valid_num(str))
		return (0);
	if (!ps_atoi(str, &value))
		return (0);
	if (has_duplicate(ps->a, value))
		return (0);
	new_node = ps_ndnew(value, 0);
	if (!new_node)
		return (0);
	ps_ndaddlast(&ps->a, new_node);
	ps->size_a++;
	return (1);
}

int	parse_numbers(t_ps *ps, char *arg)
{
	char	**numbers;
	int		i;

	numbers = ft_split(arg, ' ');
	if (!numbers)
		return (0);
	if (!numbers[0])
	{
		free_split(numbers);
		return (0);
	}
	i = 0;
	while (numbers[i])
	{
		if (!validate_one_number(ps, numbers[i]))
		{
			free_split(numbers);
			return (0);
		}
		i++;
	}
	free_split(numbers);
	return (1);
}

int	ps_parser(t_ps *ps, int ac, char **av)
{
	int	i;
	int	strat_set;
	int	flag;

	i = 1;
	strat_set = 0;
	while (i < ac)
	{
		flag = parse_flag(ps, av[i], &strat_set);
		if (flag == -1)
			return (0);
		if (flag == 0)
		{
			if (!parse_numbers(ps, av[i]))
				return (0);
		}
		i++;
	}
	return (1);
}
