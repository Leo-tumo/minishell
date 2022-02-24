/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 19:59:04 by letumany          #+#    #+#             */
/*   Updated: 2021/02/01 19:47:45 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*source;
	unsigned char		*temp;

	if (!dst && !src)
		return (NULL);
	source = (const unsigned char *)src;
	temp = (unsigned char *)dst;
	while (n)
	{
		*temp = *source;
		++source;
		++temp;
		--n;
	}
	return (dst);
}
