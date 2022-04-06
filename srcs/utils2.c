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
	g_sig.exit_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}
