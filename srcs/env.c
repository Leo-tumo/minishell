#include "../includes/minishell.h"

int	env(t_korn *korn)
{
	t_env	*tmp;

	if (korn->argc > 1)
	{
		printf("env: Unsupported arguments to env\n");
		return (1);
	}
	tmp = korn->env_head;
	while (tmp)
	{
		if (tmp->data)
		{
			ft_putstr_fd(tmp->name, korn->out);
			write(korn->out, "=", 1);
			ft_putstr_fd(tmp->name, korn->out);
			write(korn->out, "\n", 1);
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

int	env_norme(char *name, t_korn *korn)
{
	t_env *tmp;

	tmp = korn->env_head;
	while (tmp)
	{
		if (!unset_name(name))
			return (1);
		if (ft_strlen(tmp->name) == ft_strlen(korn->argv[1])
			&& !ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
				tmp->is_exported = 0;
			ft_bzero(tmp->name, ft_strlen(tmp->name));
			ft_bzero(tmp->data, ft_strlen(tmp->data));
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

/*  
** Unsets env variable
** can take many arguments
** if arg name is wrong => types error message, returns 1 and goes on
** else unsets vars, and returns 0
*/
int	unset(t_korn *korn)
{
	t_env	*tmp;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	tmp = korn->env_head;
	while (i < korn->argc)
	{
		ret += env_norme(korn->argv[i], korn);
		++i;
	}
	ft_putchar_fd('\n', korn->out);
	return (ret == 0);
}
