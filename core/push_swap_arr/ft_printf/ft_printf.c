/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/27 18:08:32 by werlim            #+#    #+#             */
/*   Updated: 2026/09/03 20:37:32 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	f_ident(const char type, va_list *list)
{
	const char	*strcheck;

	if (type == 'c')
		return (ftp_putchar(va_arg(*list, int)));
	else if (type == 's')
	{
		strcheck = va_arg(*list, char *);
		if (strcheck == NULL)
			return (ftp_putstr("(null)"));
		return (ftp_putstr(strcheck));
	}
	else if (type == 'p')
		return (handler_ptr(va_arg(*list, unsigned long)));
	else if (type == 'd' || type == 'i')
		return (handler_int(va_arg(*list, int)));
	else if (type == 'u' || type == 'x' || type == 'X')
		return (handler_unsigned(va_arg(*list, unsigned int), type));
	else if (type == '%')
		return (ftp_putchar('%'));
	else if (type == '\0')
		return (-1);
	return (-1);
}

static int	f_passby(const char *s, va_list *list)
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
			check = f_ident(s[++i], list);
			if (check == -1)
				return (-1);
			counter += check;
		}
		else
			counter += ftp_putchar(s[i]);
		i++;
	}
	return (counter);
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		charcount;

	if (!s || *s == '\0')
		return (0);
	va_start(list, s);
	charcount = f_passby(s, &list);
	va_end(list);
	return (charcount);
}
