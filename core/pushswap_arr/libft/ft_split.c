/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 16:48:37 by werlim            #+#    #+#             */
/*   Updated: 2026/08/21 19:00:35 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcounter(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[0] == '\0')
		return (count);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		count++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static size_t	wordlen(char const *s, char c, const size_t i)
{
	size_t	len;

	len = i;
	while (s[len] && s[len] != c)
		len++;
	return (len - i);
}

static char	**f_arr(char const *s, char c, char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		arr[j++] = ft_substr(s, i, wordlen(s, c, i));
		if (arr[j - 1] == NULL)
		{
			while (j > 0)
				free(arr[--j]);
			free(arr);
			return (NULL);
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	wordcount;

	if (!s)
		return (NULL);
	wordcount = wordcounter(s, c);
	arr = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (arr == NULL)
		return (NULL);
	arr[wordcount] = NULL;
	if (wordcount == 0)
		return (arr);
	else
		arr = f_arr(s, c, arr);
	return (arr);
}
/*
int main(void)
{
	char *s = "xxtestx xxxwor dlsxx ";
	char c = 'x';
	char **arr;
	int i = 0;

	arr = ft_split(s, c);
	if (arr == NULL)
		return (0);
	while (arr[i])
		printf("fmain - %s\n", arr[i++]);
	free(arr);
	return (0);
}*/
