/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 19:48:23 by letumany          #+#    #+#             */
/*   Updated: 2022/01/05 21:21:56 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*obj;

	obj = malloc(sizeof(t_list));
	if (!obj)
		return (NULL);
	obj->content = content;
	obj->next = NULL;
	return (obj);
}
