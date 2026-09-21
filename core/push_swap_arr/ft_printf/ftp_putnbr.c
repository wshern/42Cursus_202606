/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/02 20:34:18 by werlim            #+#    #+#             */
/*   Updated: 2026/09/03 20:41:39 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const char *const	g_dec = "0123456789";
static const char *const	g_hexlow = "0123456789abcdef";
static const char *const	g_hexup = "0123456789ABCDEF";

static int	ftp_putnbr(unsigned long nbr, int base, const char *alnum)
{
	char	result;
	int		counter;

	counter = 0;
	if (nbr / base == 0)
	{
		result = alnum[nbr];
		counter += ftp_putchar(result);
	}
	else
	{
		counter += ftp_putnbr((nbr / base), base, alnum);
		counter += ftp_putnbr((nbr % base), base, alnum);
	}
	return (counter);
}

int	handler_int(int nbr)
{
	int	counter;

	if (nbr == -2147483648)
		return (ftp_putstr("-2147483648"));
	counter = 0;
	if (nbr < 0)
	{
		counter += ftp_putchar('-');
		nbr = -nbr;
	}
	counter += ftp_putnbr(nbr, 10, g_dec);
	return (counter);
}

int	handler_unsigned(unsigned int nbr, char type)
{
	if (type == 'u')
		return (ftp_putnbr(nbr, 10, g_dec));
	if (type == 'x')
		return (ftp_putnbr(nbr, 16, g_hexlow));
	if (type == 'X')
		return (ftp_putnbr(nbr, 16, g_hexup));
	return (0);
}

int	handler_ptr(unsigned long nbr)
{
	int	counter;

	if (!nbr)
		return (ftp_putstr("(nil)"));
	counter = 0;
	counter += ftp_putstr("0x");
	counter += ftp_putnbr(nbr, 16, g_hexlow);
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
