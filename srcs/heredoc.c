#include "../includes/minishell.h"

/*  
** I hate libft's strncmp -> that 'n' is disgusting
*/
int		ft_strcmp(const char *s1, const char *s2)
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
** Actual heredoc is here, inside child process
*/
void	heredoc_child(t_korn *korn, int fd, char *delimiter)
{
	char	*buf;

	buf = readline("> ");
	while (buf)
	{
		korn->line++;
		ft_putendl_fd(buf, fd);
		free(buf);
		buf = readline("> ");
		if (!ft_strcmp(buf, delimiter))
		{
			free(buf);
			exit(0);
		}
		if (!buf)
		{
			printf("bash: warning: here-document at line %d delimited ", korn->line);
			printf("by end-of-file (wanted `%s')\n", delimiter);
			exit(0);
		}
	}
}

/*  
** This is fake heredoc, in case of multiple heredocs 2🍕
*/
void	fake_heredoc(t_korn *korn, char *delimiter)
{
	char	*buf;

	korn->heredoc_count--;
	buf = readline("> ");
	while (ft_strcmp(buf, delimiter))
	{
		free(buf);
		buf = readline("> ");
		korn->line++;
		if (!buf)
		{
			printf("bash: warning: here-document at line %d delimited ", korn->line);
			printf("by end-of-file (wanted `%s')\n", delimiter);
			return;
		}
	}
}

/*  
** This function allows us to get heredoc's output to STDIN
** if there are multiple heredocs, it fake them except the last one
*/
void	here_doc(t_korn *korn)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		run_signals(4);
		while (i + 1 < korn->heredoc_count)
		{
			fake_heredoc(korn, korn->delimiters[i]);
			++i;
		}
		heredoc_child(korn, fd[1], korn->delimiters[i]);
		close(fd[0]);
	}
	else
	{
		run_signals(1);
		waitpid(pid, &g_sig.exit_status, WEXITSTATUS(g_sig.exit_status));
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
}

int	main() // TODO: Just for test - I think it works!needless to say that I'm not sure about it.
{
	t_korn	*korn = malloc(sizeof(t_korn));

	korn->line = 0;
	korn->heredoc_count = 1;
	korn->delimiters = malloc(sizeof(char**));
	korn->delimiters[0] = malloc(sizeof(char *));
	korn->delimiters[0] = "eof";
	here_doc(korn);
	// while(get_next_line(0, &line))
	// 	printf("%s\n", line);
	execl("/bin/cat", "cat", NULL);
}