/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 19:11:52 by letumany          #+#    #+#             */
/*   Updated: 2022/01/07 02:46:25 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n)
	{
		if (*str1 != *str2)
		{
			if (*str1 > *str2)
				return (1);
			else
				return (-1);
		}
		++str1;
		++str2;
		--n;
	}
	return (0);
}
