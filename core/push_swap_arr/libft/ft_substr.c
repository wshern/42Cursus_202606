/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 16:08:26 by werlim            #+#    #+#             */
/*   Updated: 2026/08/06 17:36:23 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	copycount(size_t s_len, unsigned int start, size_t len)
{
	if (start > s_len)
		return (0);
	if (len < (s_len - start))
		return (len);
	else
		return ((s_len - start));
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;
	size_t	cpycount;

	if (s == NULL)
		return (NULL);
	cpycount = copycount(ft_strlen(s), start, len);
	ptr = (char *)malloc(sizeof(char) * (cpycount + 1));
	if (ptr == NULL)
		return (NULL);
	i = start;
	j = 0;
	while (j < cpycount)
		ptr[j++] = s[i++];
	ptr[j] = '\0';
	return (ptr);
}
/*
int main(void)
{
	char *str = "hello";
	char *ptr;
	
	ptr = ft_substr(str, 3, 10);
	printf("result: %s", ptr);
	free(ptr);
	return (0);
}*/
