/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:27:15 by werlim            #+#    #+#             */
/*   Updated: 2026/08/13 16:18:59 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	numlen(long n)
{
	int	i;

	if (n < 0)
		n = -n;
	i = 0;
	while (n / 10 > 0)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

static char	*placenum(long num, char *ptr, int i)
{
	ptr[i] = '\0';
	i--;
	if (num < 0)
	{
		ptr[0] = '-';
		num = -num;
	}
	while (num / 10 > 0)
	{
		ptr[i] = (num % 10) + '0';
		i--;
		num /= 10;
	}
	ptr[i] = (num % 10) + '0';
	return (ptr);
}

char	*ft_itoa(int n)
{
	long	num;
	int		numlength;
	int		isnve;
	int		i;
	char	*ptr;

	num = n;
	isnve = 0;
	if (num < 0)
		isnve = 1;
	numlength = numlen(num);
	ptr = (char *)malloc(sizeof(char) * (numlength + isnve + 1));
	if (ptr == NULL)
		return (NULL);
	i = numlength + isnve;
	return (placenum(num, ptr, i));
}
/*
#include <stdio.h>
int	main(void)
{
	char *c;
	int	n = -2147483648;

	c = ft_itoa(n);
	printf("%c\n", c[0]);
	printf("result: %s\n", c);
	free(c);
	return (0);
}*/
