/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 14:43:55 by werlim            #+#    #+#             */
/*   Updated: 2026/08/13 18:39:38 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !set)
		return (ft_strdup(""));
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	if (s1[i] == '\0')
	{
		size = 0;
		return (ft_substr(s1, i, size));
	}
	j = ft_strlen(s1) - 1;
	while (j > i && ft_strchr(set, s1[j]) != NULL)
		j--;
	size = j - i + 1;
	return (ft_substr(s1, i, size));
}
