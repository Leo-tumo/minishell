/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:01:21 by letumany          #+#    #+#             */
/*   Updated: 2022/01/05 21:22:31 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ucc;
	size_t			i;

	str = (unsigned char *)s;
	ucc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (*str == ucc)
		{
			return ((void *)(s + i));
		}
		++str;
		++i;
	}
	return (NULL);
}
