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
		if ((tmp = ft_strjoin(s1, s2)))
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
int		ft_ispace(int c)
{
	c = (unsigned char)c;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}
