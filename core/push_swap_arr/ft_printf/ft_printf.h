/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 21:58:25 by werlim            #+#    #+#             */
/*   Updated: 2026/09/03 20:37:56 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ft_printf(const char *s, ...);
int	ftp_putchar(char c);
int	ftp_putstr(const char *s);
int	handler_int(int nbr);
int	handler_unsigned(unsigned int nbr, char type);
int	handler_ptr(unsigned long nbr);

#endif