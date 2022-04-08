#include "../includes/minishell.h"

/*  
** replaces '-' & '~' with accordingly to ...
*/
char	*replace_path(char *p, t_env *head)
{
	char	*oldpwd;
	char	*home;

	home = getenv("HOME");
	oldpwd = get_value("OLDPWD", head);
	if ((p[0] == '-' && !p[1]) || (p[0] == '~' && p[1] == '-' && !p[2]))
		return (oldpwd);
	if (p[0] == '~')
	{
		if (!p[1] || (p[1] == '/' && !p[2]))
			return (home);
		else if (p[1] == '+' && !p[2])
			return (".");
		else if (ft_isalpha(p[1]) || p[1] == '_')
			return (ft_strjoin("/var/", p + 1));
		else
			return (ft_strjoin(home, p + 1));
	}
	else
		return (NULL);
}

/*
* this function converts a string to a 2d array, 
* where a[0] = string, a[1] = NULL
*/
char	**twod_array(char *str)
{
	char	**ret;

	ret = (char **)malloc(sizeof(char *) * 2);
	ret[0] = str;
	ret[1] = NULL;
	return (ret);
}

int	cd_(char *path, t_env **head)
{
	int		ret;
	char	cwd[256];
	char	*clean_path;

	getcwd(cwd, sizeof(cwd));
	if (path[0] == '-' || path[0] == '~')
		clean_path = replace_path(path, *head);
	else
		clean_path = path;
	ret = chdir(clean_path);
	if (ret == 0)
	{
		export_v(twod_array(ft_strjoin("PWD=", getcwd(NULL, 0))), head);
		export_v(twod_array(ft_strjoin("OLDPWD=", cwd)), head);
	}
	else
	{
		if (errno == 14)
			printf("bash: cd: OLDPWD not set\n");
		else
			printf("bash: cd: %s: No such file or directory\n", path);
	}
	return (ret);
}

/*  
** Gets the value of $name variable
** ex. get_value("HOME", korn->env_head)
** returns Users/letumany
*/
char	*get_value(char *name, t_env *head)
{
	t_env	*tmp;
	char	*ret;

	tmp = head;
	ret = NULL;
	while (tmp)
	{
		if (ft_strlen(tmp->name) == ft_strlen(name)
			&& (!ft_strncmp(tmp->name, name, ft_strlen(name))))
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return (NULL);
	ret = tmp->data;
	return (ret);
}
