#include "../includes/minishell.h"

void	close_2(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

/*  
** I hate libft's strncmp -> that 'n' is disgusting
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-s2[i]);
}

/*
** ^C signal in parent process
*/
void	restore_prompt(int sig)
{
	g_sig.exit_status = SIG_PLUS + sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	free2(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		++i;
	}
}

/*  
**  Same as python's str.lower()
*/
char	*lower_(char const *s)
{
	size_t		i;
	char		*ret;

	if (!s)
		return (NULL);
	i = 0;
	ret = malloc(ft_strlen(s) + 1);
	while (i < ft_strlen(s))
	{
		if (ft_isalpha(s[i]))
			ret[i] = s[i] | 1 << 5;
		else
			ret[i] = s[i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
