/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:31:35 by letumany          #+#    #+#             */
/*   Updated: 2022/01/05 21:48:16 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned char	*source;
	size_t			i;

	source = (unsigned char *)src;
	i = 0;
	if (!dst && !src)
		return ((size_t) NULL);
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0')
	{
		if (i < dstsize - 1)
		{
			*dst = *source;
			++dst;
			++source;
		}
		++i;
	}
	*dst = '\0';
	return (i);
}
