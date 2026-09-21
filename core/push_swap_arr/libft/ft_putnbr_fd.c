/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 16:35:24 by werlim            #+#    #+#             */
/*   Updated: 2026/08/18 20:45:40 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_itoa(n);
	while (str[i])
		ft_putchar_fd(str[i++], fd);
	free(str);
}

/*
#include <stdio.h>
int main(void)
{
	int i = 1234;
	int fd = 1;

	ft_putnbr_fd(i, fd);
	return (0);
}*/
