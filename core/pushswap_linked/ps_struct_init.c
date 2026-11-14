/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_struct_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 18:38:21 by werlim            #+#    #+#             */
/*   Updated: 2026/10/30 12:07:27 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	*ps_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (s);
}

void	ps_init(t_ps *ps)
{
	ps_memset(ps, 0, sizeof(*ps));
	ps->type_strat = STRAT_ADAPTIVE;
}
