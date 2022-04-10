#include "../includes/minishell.h"

/*  
**  --- closes pipe n file fd's after executions ---
*/
void	fd_closer(t_korn korn)
{
	int		i;

	i = 0;
	while (i < korn.cmd_count)
	{
		if (korn.cmd[i].input != 0)
			close(korn.cmd[i].input);
		if (korn.cmd[i].output != 1)
			close(korn.cmd[i].output);
		i++;
	}
}

/*  
** 		--- Opening pipes ---
**		--- Not sure if it's workin ---
*/
void	pi_open(t_korn *korn)
{
	int		i;
	int		*fd[2];

	i = 0;
	while (i < korn->cmd_count - 1)
	{
		if (pipe(fd[i]) == -1)
			perror("Error\nbash: ");
		if (korn->cmd[i].output == 1)
			korn->cmd[i].output = fd[i][1];
		else
			close(fd[i][1]);
		if (korn->cmd[i + 1].input == 0)
			korn->cmd[i + 1].input = fd[i][0];
		else
			close(fd[i][0]);
		++i;
	}
}
