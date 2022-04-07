#include "../includes/minishell.h"

/*  
** Prints env vars
*/
int	env_(t_korn *korn, t_cmd *cmd)
{
	t_env	*tmp;

	if (cmd->argc > 1)
	{
		printf("env: Unsupported arguments to env\n");
		g_sig.exit_status = 1;
		return (1);
	}
	tmp = korn->env_head;
	while (tmp)
	{
		if (tmp->data)
		{
			ft_putstr_fd(tmp->name, cmd->output);
			write(cmd->output, "=", 1);
			ft_putendl_fd(tmp->name, cmd->output);
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
		printf("-bash: unset: `%s': not a valid identifier\n", name);
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
		printf("KEY ==== %s\tTEMP === %s\n", key, temp->name);
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
	int		ret;

	i = 1;
	ret = 0;
	while (i < cmd->argc)
	{
		if (!is_valid_name(cmd->argv[i]))
		{
			printf("-bash: unset: `%s': not a valid identifier\n", cmd->argv[i]);
			ret = 1;
			++i;
			continue ;
		}
		printf("VAR === %s\n", cmd->argv[i]);
		delete_var(&korn->env_head, cmd->argv[i]);
		++i;
	}
	ft_putchar_fd('\n', cmd->output);
	if (ret == 0)
		g_sig.exit_status = 0;
	else
		g_sig.exit_status = 1;
	return (ret == 0);
}





/*  
** increments SHLVL anytime minishell is called
*/
void	shlvl_(t_env **env)
{
	char	*shlvl_value;
	int		shlvl;
	t_env	*tmp;

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
}
