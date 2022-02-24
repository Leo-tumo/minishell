/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:35:41 by letumany          #+#    #+#             */
/*   Updated: 2022/01/05 21:44:32 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	ucc;

	ucc = (unsigned char)c;
	if (ucc == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s)
	{
		if (*s == ucc)
		{
			return ((char *)(s));
		}
		++s;
	}
	return (NULL);
}
