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
