/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 21:29:08 by werlim            #+#    #+#             */
/*   Updated: 2026/11/10 21:29:31 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

static int	get_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

/* basically just atoi but we need to check for overflows*/
int	ps_atoi(const char *str, int *result)
{
	long	value;
	int		sign;
	int		digit;

	value = 0;
	sign = get_sign(&str);
	while (*str)
	{
		digit = *str - '0';
		if (value > 2147483648L / 10
			|| (value == 2147483648L / 10
				&& digit > 2147483648L % 10))
			return (0);
		value = value * 10 + digit;
		str++;
	}
	value *= sign;
	if (value < INT_MIN || value > INT_MAX)
		return (0);
	*result = (int)value;
	return (1);
}
