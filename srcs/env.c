/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:56:02 by letumany          #+#    #+#             */
/*   Updated: 2022/04/20 00:56:26 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  
** Prints env vars
*/
int	env_(t_korn *korn, t_cmd *cmd)
{
	t_env	*tmp;

	if (cmd->argc > 1)
	{
		ft_putendl_fd("env: Unsupported arguments to env", 2);
		return (1);
	}
	tmp = korn->env_head;
	while (tmp)
	{
		if (tmp->data)
		{
			ft_putstr_fd(tmp->name, cmd->output);
			write(cmd->output, "=", 1);
			ft_putendl_fd(tmp->data, cmd->output);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*  
** Unsets variable from my env
*/
int	unset_name(char *name)
{
	if (is_valid_name(name))
		return (TRUE);
	else
	{
		ft_putstr_fd("bash: unset: `", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return (FALSE);
	}
}

/*  
** 		--Finds var in linked list and deletes it
**		used double pointer, in case of the needed
**		var is also the head of struct
*/
void	delete_var(t_env **head, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head;
	if (temp != NULL && (ft_strcmp(temp->name, key) == 0))
	{
		*head = temp->next;
		free(temp);
		return ;
	}
	while (temp != NULL && (ft_strcmp(temp->name, key) != 0))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return ;
	prev->next = temp->next;
	free(temp);
}

/*  
** Unsets env variable
** can take many arguments
** if arg name is wrong => types error message, returns 1 and goes on
** else unsets vars, and returns 0
*/
int	unset_(t_korn *korn, t_cmd *cmd)
{
	int		i;

	if (cmd->argv[1][0] == '-')
	{
		ft_putstr_fd("bash: unset: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": invalid option", 2);
		return (2);
	}
	i = 1;
	while (i < cmd->argc)
	{
		delete_var(&korn->env_head, cmd->argv[i]);
		++i;
	}
	ft_putchar_fd('\n', cmd->output);
	return (0);
}

/*  
** increments SHLVL anytime minishell is called
*/
void	shlvl_(t_env **env)
{
	char	*shlvl_value;
	int		shlvl;
	t_env	*tmp;
	char	**s;

	tmp = *env;
	shlvl_value = getenv("SHLVL");
	if (ft_strcmp(shlvl_value, "") == 0)
		return ;
	shlvl = (int)ft_atoi(shlvl_value) + 1;
	while (tmp && tmp->next)
	{
		if (ft_strncmp("SHLVL", tmp->name, 5) == 0)
		{
			tmp->data = ft_itoa(shlvl);
			break ;
		}
		tmp = tmp->next;
	}
	s = malloc(3 * sizeof(char *));
	s[0] = "export";
	s[1] = "PS1=\001\033[1;35m\002Can I get your number? \001\033[0m\002";
	s[2] = NULL;
	export_v(s, *env);
}
