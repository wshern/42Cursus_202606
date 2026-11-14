/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 16:45:56 by werlim            #+#    #+#             */
/*   Updated: 2026/08/03 21:41:39 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;

	dstlen = 0;
	while (dstlen < dstsize && dst[dstlen])
		dstlen++;
	if (dstlen == dstsize)
		return (dstsize + ft_strlen(src));
	i = 0;
	j = dstlen;
	while (i < dstsize - dstlen - 1 && src[i])
	{
		dst[j] = src[i];
		j++;
		i++;
	}
	dst[j] = '\0';
	return (dstlen + ft_strlen(src));
}
