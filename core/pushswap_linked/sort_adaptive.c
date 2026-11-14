/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 18:33:19 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 20:41:21 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_ps *ps)
{
	double	disorder;

	disorder = ps->disorder;
	if (disorder < 0.2)
		sort_simple(ps);
	else if (disorder >= 0.2 && disorder < 0.5)
		sort_medium(ps);
	else
		sort_complex(ps);
}
