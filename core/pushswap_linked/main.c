/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:45:47 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 17:37:05 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_ps	ps;

	if (ac < 2)
		return (0);
	ps_init(&ps);
	if (!ps_parser(&ps, ac, av) || ps.size_a == 0)
	{
		ps_ndclear(&ps.a);
		ps_ndclear(&ps.b);
		ps_printf(2, "Error\n");
		return (0);
	}
	assign_rank(ps.a);
	ps_dispatcher(&ps);
	if (ps.bench == 1)
		bench(&ps);
	ps_ndclear(&ps.a);
	ps_ndclear(&ps.b);
	return (0);
}
