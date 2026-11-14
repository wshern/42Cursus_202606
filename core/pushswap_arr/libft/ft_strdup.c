/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 16:54:00 by werlim            #+#    #+#             */
/*   Updated: 2026/08/05 18:34:09 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char	*ft_strdup(const char *s1)
{
	char		*ptr;
	size_t		strlength;
	size_t		i;

	strlength = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (strlength + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}*/

char	*ft_strdup(const char *s1)
{
	char		*ptr;
	size_t		strlength;

	strlength = ft_strlen(s1);
	ptr = (char *)malloc(sizeof(char) * (strlength + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1, strlength + 1);
	return (ptr);
}
