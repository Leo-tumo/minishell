#include "../includes/minishell.h"

/*  
** Check id Var name is valid
** it can only be _ or letters 
** ex. _VAr="some sh*t", _VAr+=77777
*/
int	is_valid_name(char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (FALSE);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			if (!(*str == '+' && *(str +1) && *(str + 1) == '='))
				return (FALSE);
		str++;
	}
	return (TRUE);
}

/*  
** export without arguments , just printing list
*/
int	export(int fd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(tmp->name, fd);
		if (tmp->data)
		{
			write(fd, "=\"", 2);
			ft_putstr_fd(tmp->data, fd);
			write(fd, "\"\n", 2);
		}
		tmp = tmp->next;
	}
	return (0);
}

/*  
** export with arguments
*/
int	export_(char**s, t_env *head)
{
	int		i;
	int		sign;
	int		empty_value;
	int		ret;

	i = 0;
	ret = 0;
	while (s[i] != NULL)
	{
		if (!(is_valid_name(s[i])))
		{
			printf("bash: export: `%s': not a valid identifier\n", s[i]);
			ret = 1;
			++i;
			continue ;
		}
		sign = export_append(s[i]);
		empty_value = check_value(s[i]);
		if (check_existance(s[i], head))
			renew_var(s[i], sign, empty_value, head);
		else
			append_var(s[i], sign * 10 + empty_value, head, 1);
		++i;
	}
	return (ret);
}

void	append_var(char *str, int flags, t_env *head, int is_exported)
{
	t_env	*tmp;
	char	**var;
	int		sign;
	int		empty_value;
	char	*key;

	tmp = head;
	key = NULL;
	var = env_split(str);
	sign = flags / 10;
	empty_value = flags % 10;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = malloc(sizeof(t_env));
	tmp->next->next = NULL;
	tmp->next->is_exported = is_exported;
	if (sign)
		key = remove_plus_sign(var[0]);
	else
		key = var[0];
	tmp->next->name = key;
	if (empty_value)
		tmp->next->data = var[1];
}

/*  
** removes plus sign from var_name
*/
char	*remove_plus_sign(char *s)
{
	int		i;
	char	*new_name;

	i = 0;
	new_name = (char *)malloc(ft_strlen(s) + 1);
	while (s[i])
	{
		new_name[i] = s[i];
		if (s[i] == '+')
		{
			new_name[i] = '\0';
			break ;
		}
		++i;
	}
	return (new_name);
}
