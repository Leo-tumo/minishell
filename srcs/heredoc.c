#include "../includes/minishell.h"

void	here_doc(t_doc *doc)
{
	int		fd[2];
	char	*buf;
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		write(1, "> ", 2);
		while (get_next_line(1, &buf))
		{
			if (!ft_strcmp(buf, doc->delimiter))
				exit(0);
			write(1, "> ", 2);
			ft_putendl_fd(buf, fd[1]);
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &g_sig.exit_status, WEXITSTATUS(g_sig.exit_status));
	}
}