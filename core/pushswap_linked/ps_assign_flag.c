/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_assign_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 21:32:52 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 21:33:01 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	set_strategy(t_ps *ps, int *strat_set, int strategy)
{
	if (*strat_set)
		return (-1);
	ps->type_strat = strategy;
	*strat_set = 1;
	return (1);
}

int	parse_flag(t_ps *ps, char *arg, int *strat_set)
{
	if (ft_strncmp(arg, "--simple", 9) == 0)
		return (set_strategy(ps, strat_set, STRAT_SIMPLE));
	if (ft_strncmp(arg, "--medium", 9) == 0)
		return (set_strategy(ps, strat_set, STRAT_MEDIUM));
	if (ft_strncmp(arg, "--complex", 10) == 0)
		return (set_strategy(ps, strat_set, STRAT_COMPLEX));
	if (ft_strncmp(arg, "--adaptive", 11) == 0)
		return (set_strategy(ps, strat_set, STRAT_ADAPTIVE));
	if (ft_strncmp(arg, "--bench", 8) == 0)
	{
		ps->bench = 1;
		return (1);
	}
	if (arg[0] == '-' && arg[1] == '-')
		return (-1);
	return (0);
}
