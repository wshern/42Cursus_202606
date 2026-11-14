/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 22:57:03 by werlim            #+#    #+#             */
/*   Updated: 2026/09/21 00:58:03 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int ac, char **av)
{
	t_carr	s_a;
	t_carr	s_b;
	int capacity;

	capacity = check_input(av);
	if (!arr_init(&s_a, capacity))
		return (1);
	return (0);
}