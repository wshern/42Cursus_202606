/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 16:53:10 by werlim            #+#    #+#             */
/*   Updated: 2026/08/13 18:31:36 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	i;
	size_t	strlength;

	if (!s || !f)
		return (NULL);
	strlength = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (strlength + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < strlength)
	{
		ptr[i] = f((unsigned int)i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
