/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 20:03:35 by letumany          #+#    #+#             */
/*   Updated: 2022/01/05 21:10:24 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbrlen(int nbr)
{
	int	i;

	if (nbr <= 0)
		i = 1;
	else
		i = 0;
	if (nbr < 0)
		nbr *= -1;
	while (nbr)
	{
		nbr /= 10;
		++i;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	int		len;

	nbr = n;
	len = nbrlen(nbr);
	str = malloc(sizeof(unsigned char) * (len + 1));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr *= -1;
		str[0] = '-';
	}
	if (nbr == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (nbr)
	{
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
		--len;
	}
	return (str);
}
