/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:26:29 by letumany          #+#    #+#             */
/*   Updated: 2022/03/18 14:06:32 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	newstrlen;
// 	char	*newstr;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	newstrlen = ft_strlen(s1) + ft_strlen(s2);
// 	newstr = malloc(sizeof(char *) * newstrlen + 1);
// 	if (!newstr)
// 		return (NULL);
// 	while (*s1 != '\0')
// 	{
// 		*newstr = *s1;
// 		++s1;
// 		++newstr;
// 	}
// 	while (*s2 != '\0')
// 	{
// 		*newstr = *s2;
// 		++s2;
// 		++newstr;
// 	}
// 	*newstr = '\0';
// 	return (newstr - newstrlen);
// }
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}