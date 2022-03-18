#include "../includes/minishell.h"

/*  
** Checks if var should append or replace - '=' vs '+='
*/
int	export_append(char *s)
{
	int	i;

	i = 0;
	while (ft_isalnum(s[i]) || s[i] == '_')
		++i;
	if (s[i] == '+')
		return (True);
	else
		return (False);
}

/*  
** Checks if variable has value or is empty
*/
int	check_value(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		++i;
	if (s[i] == '=')
		++i;
	if (!s[i] || s[i] == ' ')
		return (False);
	else
		return (True);
}

/*  
** Check if the variable that will be exported
** is new or already exists
*/
int	check_existance(char *s, t_env *head)
{
	t_env		*tmp;
	size_t		i;

	i = 0;
	tmp = head;
	while (s[i])
	{
		if (s[i] == '+' || s[i] == '=')
			break ;
		++i;
	}
	while (tmp)
	{
		if (i == ft_strlen(tmp->name))
		{
			if (ft_strncmp(s, tmp->name, i) == 0)
				return (True);
		}
		tmp = tmp->next;
	}
	return (False);
}

/*  
** Splitted function for norminette
*/
void	renew_var_norme(char **new_var, int has_value, t_env *head)
{
	char	*name;
	t_env	*tmp;

	tmp = head;
	name = remove_plus_sign(new_var[0]);
	while (ft_strncmp(name, tmp->name, ft_strlen(name) + 1) != 0)
			tmp = tmp->next;
	tmp->is_exported = 1;
	if (has_value)
	{
		name = ft_strjoin(tmp->data, new_var[1]);
		tmp->data = name;
	}
}

/*  
** Exports or renews existing var, with new value &
** sets is_exported flag to 1
*/
void	renew_var(char *new_var, int append, int has_value, t_env *head)
{
	t_env	*tmp;
	int		i;
	char	**var;

	var = NULL;
	var = env_split(new_var);
	tmp = head;
	i = 0;
	if (!append)
	{
		while (tmp)
		{
			if (ft_strlen(tmp->name) == ft_strlen(var[0]))
				if (!ft_strncmp(tmp->name, var[0], ft_strlen(var[0])))
					break ;
			tmp = tmp->next;
		}
		tmp->is_exported = 1;
		free(tmp->data);
		if (has_value)
			tmp->data = ft_strdup(var[1]);
	}
	else
		renew_var_norme(var, has_value, head);
	free(var);
}
