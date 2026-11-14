/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:38:10 by ukperei           #+#    #+#             */
/*   Updated: 2026/11/10 18:57:10 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_small_num(t_ps *ps)
{
	if (ps->size_a == 2)
		sort_two(ps);
	else if (ps->size_a == 3)
		sort_three(ps);
	else if (ps->size_a == 4)
		sort_four(ps);
	else if (ps->size_a == 5)
		sort_five(ps);
}

void	sort_simple(t_ps *ps)
{
	ps->type_class = STRAT_SIMPLE;
	if (try_rotation_sorting(ps))
		return ;
	if (ps->size_a < 6)
		sort_small_num(ps);
	else
		sort_simple_all(ps);
}
