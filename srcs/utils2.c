#include "../includes/minishell.h"

void	close_2(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}