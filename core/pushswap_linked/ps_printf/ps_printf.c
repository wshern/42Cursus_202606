/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:08:32 by werlim            #+#    #+#             */
/*   Updated: 2026/10/15 14:14:53 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ps_printf.h"
#include <stdarg.h>

static int	f_ident(const int fd, const char type, va_list *list)
{
	const char	*strcheck;

	if (type == 'c')
		return (ps_putchar(fd, va_arg(*list, int)));
	else if (type == 's')
	{
		strcheck = va_arg(*list, char *);
		if (strcheck == NULL)
			return (ps_putstr(fd, "(null)"));
		return (ps_putstr(fd, strcheck));
	}
	else if (type == 'p')
		return (handler_ptr(fd, va_arg(*list, unsigned long)));
	else if (type == 'd' || type == 'i')
		return (handler_int(fd, va_arg(*list, int)));
	else if (type == 'u' || type == 'x' || type == 'X')
		return (handler_unsigned(fd, va_arg(*list, unsigned int), type));
	else if (type == '%')
		return (ps_putchar(fd, '%'));
	else if (type == '\0')
		return (-1);
	else if (type == 'f')
		return (handler_putfloat(fd, va_arg(*list, double)));
	return (-1);
}

static int	f_passby(const int fd, const char *s, va_list *list)
{
	int	i;
	int	counter;
	int	check;

	i = 0;
	counter = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			check = f_ident(fd, s[++i], list);
			if (check == -1)
				return (-1);
			counter += check;
		}
		else
			counter += ps_putchar(fd, s[i]);
		i++;
	}
	return (counter);
}

int	ps_printf(const int fd, const char *s, ...)
{
	va_list	list;
	int		charcount;

	if (!s || *s == '\0')
		return (0);
	va_start(list, s);
	charcount = f_passby(fd, s, &list);
	va_end(list);
	return (charcount);
}
