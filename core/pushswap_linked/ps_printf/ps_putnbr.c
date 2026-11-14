/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:34:18 by werlim            #+#    #+#             */
/*   Updated: 2026/10/15 12:52:24 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_printf.h"

static int	ps_putnbr(const int fd, unsigned long nbr,
	int base, const char *alnum)
{
	char	result;
	int		counter;

	counter = 0;
	if (nbr / base == 0)
	{
		result = alnum[nbr];
		counter += ps_putchar(fd, result);
	}
	else
	{
		counter += ps_putnbr(fd, (nbr / base), base, alnum);
		counter += ps_putnbr(fd, (nbr % base), base, alnum);
	}
	return (counter);
}

int	handler_int(const int fd, int nbr)
{
	int	counter;

	if (nbr == -2147483648)
		return (ps_putstr(fd, "-2147483648"));
	counter = 0;
	if (nbr < 0)
	{
		counter += ps_putchar(fd, '-');
		nbr = -nbr;
	}
	counter += ps_putnbr(fd, nbr, 10, "0123456789");
	return (counter);
}

int	handler_unsigned(const int fd, unsigned int nbr, char type)
{
	if (type == 'u')
		return (ps_putnbr(fd, nbr, 10, "0123456789"));
	if (type == 'x')
		return (ps_putnbr(fd, nbr, 16, "0123456789abcdef"));
	if (type == 'X')
		return (ps_putnbr(fd, nbr, 16, "0123456789ABCDEF"));
	return (0);
}

int	handler_ptr(const int fd, unsigned long nbr)
{
	int	counter;

	if (!nbr)
		return (ps_putstr(fd, "(nil)"));
	counter = 0;
	counter += ps_putstr(fd, "0x");
	counter += ps_putnbr(fd, nbr, 16, "0123456789abcdef");
	return (counter);
}

int	handler_putfloat(const int fd, double nbr)
{
	int	n1;
	int	n2;
	int	counter;

	counter = 0;
	n1 = (int)(nbr * 100 + 0.5) / 100;
	n2 = (int)(nbr * 100 + 0.5) % 100;
	counter += handler_int(fd, n1);
	counter += ps_putchar(fd, '.');
	if (n2 < 10)
		counter += ps_putchar(fd, '0');
	counter += handler_int(fd, n2);
	return (counter);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int				n;
// 	unsigned int	u;
// 	unsigned long	p;
// 	char			type;

// 	printf("=== d / i ===\n");

// 	n = 42;
// 	handler_int(n);
// 	printf("\n");

// 	n = -42;
// 	handler_int(n);
// 	printf("\n");

// 	n = -2147483648;
// 	handler_int(n);
// 	printf("\n");

// 	printf("\n=== u ===\n");

// 	u = 42;
// 	type = 'u';
// 	handler_unsigned(u, type);
// 	printf("\n");

// 	u = 4294967295;
// 	handler_unsigned(u, type);
// 	printf("\n");

// 	printf("\n=== x ===\n");

// 	u = 255;
// 	type = 'x';
// 	handler_unsigned(u, type);
// 	printf("\n");

// 	printf("\n=== X ===\n");

// 	type = 'X';
// 	handler_unsigned(u, type);
// 	printf("\n");

// 	printf("\n=== p ===\n");

// 	p = 42;
// 	handler_ptr(p);
// 	printf("\n");

// 	p = 0;
// 	handler_ptr(p);
// 	printf("\n");

// 	return (0);
// }
