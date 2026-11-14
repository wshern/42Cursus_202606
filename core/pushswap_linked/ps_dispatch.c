/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 17:21:51 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:59:08 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ps_dispatcher(t_ps *ps)
{
	ps->disorder = calc_disorder(ps->a);
	if (ps->disorder == 0.0)
	{
		if (ps->type_strat == STRAT_ADAPTIVE)
			ps->type_class = STRAT_SIMPLE;
		else
			ps->type_class = ps->type_strat;
		return ;
	}
	if (ps->type_strat == STRAT_SIMPLE)
		sort_simple(ps);
	else if (ps->type_strat == STRAT_MEDIUM)
		sort_medium(ps);
	else if (ps->type_strat == STRAT_COMPLEX)
		sort_complex(ps);
	else
		sort_adaptive(ps);
}
