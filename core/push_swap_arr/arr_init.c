/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 22:58:50 by werlim            #+#    #+#             */
/*   Updated: 2026/09/21 00:58:01 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void arr_free(t_carr *s)
{
	free(s->arr);
	s->arr = NULL;
	s->head = 0;
	s->size = 0;
	s->capacity = 0;
}

int arr_init(t_carr *s, int capacity)
{
	s->head = 0;
	s->capacity = capacity;
	s->size = 0;
	s->arr = malloc(sizeof(int) * capacity);
	if (!s->arr)
		return (0);
	return (1);
}