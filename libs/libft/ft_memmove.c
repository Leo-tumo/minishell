/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:54:42 by letumany          #+#    #+#             */
/*   Updated: 2021/01/30 18:58:43 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*source;
	unsigned char		*destination;

	if (!dst && !src)
		return (NULL);
	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if ((source < destination) && (destination < source + len))
	{
		destination += len;
		source += len;
		while (len)
		{
			*(--destination) = *(--source);
			--len;
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
