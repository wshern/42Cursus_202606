/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: werlim <werlim@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:27:57 by werlim            #+#    #+#             */
/*   Updated: 2026/08/03 21:40:00 by werlim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ie s="abc", strlen = 3 => i = 3 + 1 is because (i-- > 0) condition
// so (i = 4 > 0) => correct, then i-- becomes 3 which is null terminator
char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	char_c;

	i = ft_strlen(s) + 1;
	char_c = (char)c;
	while (i-- > 0)
	{
		if (s[i] == char_c)
			return ((char *)&s[i]);
	}
	return (NULL);
}
