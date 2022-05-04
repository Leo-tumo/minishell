/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:05:54 by letumany          #+#    #+#             */
/*   Updated: 2022/04/16 11:19:45 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		**fd;

	fd = malloc(sizeof(int *) * (korn->cmd_count) * 2);
	i = 0;
	while (i < korn->cmd_count - 1)
	{
		fd[i] = malloc(sizeof(int) * 2);
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

void	close_one(t_cmd *cmd)
{
	if (cmd->output != 1)
		close(cmd->output);
	if (cmd->input != 0)
		close(cmd->input);
}

void	close_them(t_korn *korn, int index)
{
	int	i;

	i = 0;
	while (i < korn->cmd_count - 1)
	{
		if (i != index)
		{
			if (korn->cmd[0].input)
				close(korn->cmd[0].input);
			if (korn->cmd[0].output != 1)
				close(korn->cmd[0].output);
		}
		++i;
	}
}
