/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:56:19 by letumany          #+#    #+#             */
/*   Updated: 2022/04/16 09:15:27 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  
** 		Executes binary file
** 		Note: execve works this way
** 		execve("/bin/cat", argv, NULL);
** 		where argv should be =>    
** 		"cat", "-e", "file1", "file2" 
*/
void	exec_bin(t_korn *korn, int i)
{
	char	**env;

	run_signals(2);
	close_them(korn, i);
	if (korn->cmd[i].input != 0)
		dup2(korn->cmd[i].input, STDIN_FILENO);
	if (korn->cmd[i].output != 1)
	{
		dup2(korn->cmd[i].output, STDOUT_FILENO);
	}
	env = ll_to_matrix(korn->env_head);
	if (!guns_n_roses(korn->cmd[i].name))
	{
		pathfinder(&korn->cmd[i], korn);
		execve(korn->cmd[i].path, korn->cmd[i].argv, env);
	}
	else
		execve(korn->cmd[i].name, korn->cmd[i].argv, env);
}

/*  
** This func executes the --BUILTIN-- commands
*/
void	exec_(t_cmd *cmd, t_korn *korn)
{
	if (cmd->id == 1)
		cmd->stat = echo_(cmd);
	if (cmd->id == 2)
		cmd->stat = cd_(cmd->argv[1], korn->env_head);
	if (cmd->id == 3)
		cmd->stat = pwd_(*cmd, korn->env_head);
	if (cmd->id == 4)
	{
		if (cmd->argc == 1)
			cmd->stat = export_p(cmd->output, korn->env_head);
		else
			cmd->stat = export_v(cmd->argv, korn->env_head);
	}
	if (cmd->id == 5)
		cmd->stat = unset_(korn, cmd);
	if (cmd->id == 6)
		cmd->stat = env_(korn, cmd);
	if (cmd->id == 7)
		cmd->stat = exit_(cmd, korn);
}

/*
** 		--- Waits for child processes ---
*/
void	waiter(t_korn *korn)
{
	int		i;
	pid_t	pid;
	int		stat;
	t_cmd	*finished;

	i = 0;
	while (i < korn->cmd_count)
	{
		pid = wait(&stat);
		if (pid == korn->child[korn->cmd_count - 1])
		{
			if (korn->cmd[korn->cmd_count - 1].id == 0)
				g_sig.exit_status = WEXITSTATUS(stat);
		}
		if (WTERMSIG(stat))
			g_sig.exit_status = WTERMSIG(stat) + SIG_PLUS;
		finished = find_child(korn, pid);
		if (finished)
			close_one(finished);
		i++;
	}
	fd_closer(*korn);
	if (korn->cmd[korn->cmd_count - 1].id > 0)
		g_sig.exit_status = korn->cmd[korn->cmd_count - 1].stat;
}

/*
** 	--- Forks processes for childs ---
*/
void	incubator(t_korn *korn)
{
	int	i;

	i = 0;
	while (i < korn->cmd_count)
	{
		korn->child[i] = fork();
		if (korn->child[i] == 0)
		{
			korn->cmd[i].id = is_builtin(korn->cmd[i]);
			if (korn->cmd[i].id == 0)
			{
				if (!korn->cmd[i].argv)
					exit(0);
				exec_bin(korn, i);
			}
			else
				exec_(&korn->cmd[i], korn);
			exit(1);
		}
		i++;
	}
	waiter(korn);
}

/*  
** ---	The King of Execution ---
*/
void	processor(t_korn *korn)
{
	if (korn->cmd_count > 1)
		pi_open(korn);
	if ((korn->cmd_count == 1) && (is_builtin(korn->cmd[0]) > 0))
		exec_(&korn->cmd[0], korn);
	else
		incubator(korn);
}
