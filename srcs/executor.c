#include "../includes/minishell.h"

/*  
** 		Executes binary file
** 		Note: execve works this way
** 		execve("/bin/cat", argv, NULL);
** 		where argv should be =>    
** 		"cat", "-e", "file1", "file2" 
*/
void	exec_bin(t_cmd *cmd, t_korn *korn)
{
	char	**env;

	run_signals(2);
	if (cmd->input != 0)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output != 1)
		dup2(cmd->output, STDOUT_FILENO);
	env = ll_to_matrix(korn->env_head);
	for(int i = 0; env[i]; ++i)
		printf("ENV[%d] = %s\n", i, env[i]);
	if (!guns_n_roses(cmd->name))
	{
		pathfinder(cmd, korn);
		execve(cmd->path, cmd->argv, env); // FIXME:
		printf("PATH == %s, ARGV == %s\n", cmd->path, cmd->argv[0]);
		// printf("HELLO WORLD\n");
	}
	else
		execve(cmd->name, cmd->argv, env);
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
		cmd->stat = exit_(cmd);
}

/*
** 		--- Waits for child processes ---
*/
void	waiter(t_korn *korn)
{
	int	i;
	int	stat;
	// int	signaled;

	i = 0;
	while (i < korn->cmd_count)
	{
		if (wait(&stat) == korn->child[korn->cmd_count - 1])
		{
			if (korn->cmd[korn->cmd_count - 1].id == 0)
				g_sig.exit_status = WEXITSTATUS(stat);
		}
		if (WTERMSIG(stat))
			g_sig.exit_status = WTERMSIG(stat) + SIG_PLUS;
		i++;
	}
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
			// korn->cmd[i].id = is_builtin(korn->cmd[i]);
			if (korn->cmd[i].id == 0)
			{
				if (!korn->cmd[i].argv)
					exit(0);
				exec_bin(&korn->cmd[i], korn);
			}
			else
			{
				exec_(&korn->cmd[i], korn);
			}
			exit(1);
		}
		i++;
	}
	waiter(korn);
}
