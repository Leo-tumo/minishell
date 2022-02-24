/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:02:30 by letumany          #+#    #+#             */
/*   Updated: 2021/01/28 20:19:21 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*source;
	unsigned char	*temp;
	unsigned char	ucc;
	size_t			i;

	source = (unsigned char *)src;
	temp = (unsigned char *)dst;
	ucc = (unsigned char)c;
	i = 0;
	while (++i <= n)
	{
		*temp = *source;
		if (*source == ucc)
		{
			return (dst + i);
		}
		++source;
		++temp;
	}
	return (NULL);
}
