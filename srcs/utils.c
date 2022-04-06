#include "../includes/minishell.h"

/*  
** Allocates (with malloc) and returns a new
** string, which is the result of the concatenation
** of 's1' + 's2' + 's3'.
*/
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;

	tmp = NULL;
	if (s1 && s2 && s3)
	{
		tmp = ft_strjoin(s1, s2);
		if (tmp)
			tmp = ft_strjoin(tmp, s3);
	}
	return (tmp);
}

/*
** Checks if there's a SLASH in command name or not
** ./a.out - returns TRUE (1)
** mkdir - returns FALSE (0)
*/
int	guns_n_roses(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			return (TRUE);
		++i;
	}
	return (FALSE);
}

/*  
** Libft is sick
*/
int	ft_ispace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

/*  
** 		-- adds a char at the end of string
**		-- and returns the new string
*/
int	char_join(char c, char **s1)
{
	int		i;
	char	*str;

	str = NULL;
	if (!(*s1))
	{
		str = malloc(2);
		str[0] = c;
		str[1] = '\0';
		*s1 = ft_strdup(str);
		free(str);
		return (1);
	}
	i = ft_strlen(*s1);
	str = (char *)malloc(i + 2);
	ft_memcpy(str, *s1, i);
	str[i] = c;
	str[i + 1] = '\0';
	ft_memdel((void **)s1);
	*s1 = ft_strdup(str);
	free(str);
	return (1);
}

/*  
** 		replaces $ var with it's value
**		not sure bout memdel(var_name) ???
*/
char	*repl_dollar(char *ret, char **var_name, char **str, t_env *env)
{
	char_join(**str, var_name);
	(*str)++;
	while (ft_isalnum(**str) || **str == '_')
		*str += char_join(**str, var_name);
	if (get_value(*var_name, env))
	{	
		if (ret)
			ret = ft_strjoin(ret, get_value(*var_name, env));
		else
			ret = ft_strdup(get_value(*var_name, env));
	}
	ft_memdel((void **)var_name);
	return (ret);
}
