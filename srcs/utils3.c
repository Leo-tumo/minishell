/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:07:07 by letumany          #+#    #+#             */
/*   Updated: 2022/04/15 15:07:08 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Transforms linked list to char**
*/
char	**ll_to_matrix(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**array;

	i = 0;
	tmp = env;
	array = malloc(sizeof(char *) * 100);
	while (tmp != NULL)
	{
		if (tmp->data)
			array[i] = ft_strjoin3(tmp->name, "=", tmp->data);
		else
			array[i] = tmp->name;
		i++;
		tmp = tmp->next;
	}
	return (array);
}

/*  
** Find the child with pid
*/
t_cmd	*find_child(t_korn *korn, pid_t pid)
{
	int	i;

	i = 0;
	while (i < korn->cmd_count)
	{
		if (korn->child[i] == pid)
			return (&korn->cmd[i]);
		i++;
	}
	return (NULL);
}
