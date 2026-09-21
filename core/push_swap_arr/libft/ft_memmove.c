/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 16:48:54 by werlim            #+#    #+#             */
/*   Updated: 2026/08/03 21:42:55 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*p_dest;
	const unsigned char	*p_src;

	if (dest == NULL && src == NULL)
		return (dest);
	p_dest = (unsigned char *)dest;
	p_src = (const unsigned char *)src;
	if (dest < src)
		ft_memcpy(dest, src, len);
	else
	{
		i = len;
		while (i-- > 0)
			p_dest[i] = p_src[i];
	}
	return (dest);
}
