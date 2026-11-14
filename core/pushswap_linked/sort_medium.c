/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_medium.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 14:38:10 by ukperei           #+#    #+#             */
/*   Updated: 2026/11/10 20:31:31 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_medium_passby(t_ps *ps)
{
	int	size;
	int	chunk_size;
	int	start;
	int	end;

	size = ps->size_a;
	chunk_size = get_chunk_size(size);
	start = 0;
	end = chunk_size;
	while (start < size)
	{
		while (chunk_remainder(ps->a, start, end))
		{
			if (in_chunk(ps->a, start, end))
				op_pb(ps);
			else
				op_ra(ps);
		}
		start += chunk_size;
		end += chunk_size;
	}
	push_sorted_b(ps);
}

void	sort_medium(t_ps *ps)
{
	ps->type_class = STRAT_MEDIUM;
	if (try_rotation_sorting(ps))
		return ;
	if (ps->size_a < 6)
	{
		sort_small_num(ps);
		return ;
	}
	sort_medium_passby(ps);
}
