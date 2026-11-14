/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 21:58:25 by werlim            #+#    #+#             */
/*   Updated: 2026/10/15 14:31:46 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PS_PRINTF_H
# define PS_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

int	ps_printf(const int fd, const char *s, ...);
int	ps_putchar(const int fd, char c);
int	ps_putstr(const int fd, const char *s);
int	handler_int(const int fd, int nbr);
int	handler_unsigned(const int fd, unsigned int nbr, char type);
int	handler_ptr(const int fd, unsigned long nbr);
int	handler_putfloat(const int fd, double nbr);

#endif