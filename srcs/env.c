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
// /*  
// ** 		--- util for unset ---
// */
// int	env_norme(char *name, t_korn *korn, t_cmd *cmd)
// {
// 	t_env *tmp;

// 	tmp = korn->env_head;
// 	while (tmp)
// 	{
// 		if (!unset_name(name))
// 			return (1);
// 		if (ft_strlen(tmp->name) == ft_strlen(korn->argv[1])
// 			&& !ft_strncmp(tmp->name, name, ft_strlen(name)))
// 		{
// 				tmp->blind = 0;
// 			ft_bzero(tmp->name, ft_strlen(tmp->name));
// 			ft_bzero(tmp->data, ft_strlen(tmp->data));
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

/*  
** 		--Finds var in linked list and deletes it
**		used double pointer, in case of the needed
**		var is also the head of struct
*/
void delete_var(t_env **head, char *key)
{
    t_env	*temp;
	t_env	*prev;

	temp = *head;
    if (temp != NULL && (ft_strcmp(temp->name, key) == 0))
	{
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && (ft_strcmp(temp->name, key) != 0))
	{
		printf("KEY ==== %s\tTEMP === %s\n", key, temp->name);
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
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
			continue;
		}
		printf("VAR === %s\n", cmd->argv[i]);
		delete_var(&korn->env_head, cmd->argv[i]);
		++i;
	}
	ft_putchar_fd('\n', korn->out);
	if (ret == 0)
		g_sig.exit_status = 0;
	else
		g_sig.exit_status = 1;
	return (ret == 0);
}

extern char **environ;

int	main() //FIXME:
{
	t_korn	*korn = malloc(sizeof(t_korn));

	t_env	*env = malloc(sizeof(t_env));
	env = env_keeper(environ);
	korn->env_head = env;
	t_cmd *cmd = malloc(sizeof(t_cmd));
	cmd->argv = ft_split("unset b c", ' ');
	cmd->argc = 3;
	

	export_v(ft_split("export a=a b=bababe c=dsaffd", ' '), env);
	// printf("A === %s\n$? === %d\n", get_value("c", env), g_sig.exit_status);
	unset_(korn, cmd);
	export_p(1, env);
	printf("$? === %d\n", g_sig.exit_status);
	
}
