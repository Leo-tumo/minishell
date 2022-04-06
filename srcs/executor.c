#include "../includes/minishell.h"

/*  
** Executes binary file
** Note: execve works this way
** execve("/bin/cat", argv, NULL);
** where argv should be =>
** "cat", "-e", "file1", "file2" 
*/
void	exec_bin(t_cmd *cmd)
{
	run_signals(2);
	dup2(cmd->input, STDIN_FILENO);
	dup2(cmd->output, STDOUT_FILENO);
	execve(cmd->path, cmd->argv, NULL);
	close(cmd->input);
	close(cmd->output);
}

/*
** 	--- Forks processes for childs ---
*/
void	incubator(t_korn *korn)
{
	int	i;

	if (korn->cmd_count == 1 && korn->cmd[0]->argv 
			&& is_builtin(korn->cmd[0]->argv[0]))
		cmd_switch(korn->cmd[0], korn);
	else
	{
		i = 0;
		while (i < korn->cmd_count)
		{
			korn->child = fork();
			if (korn->child == 0)
			{
				if (!korn->cmd[i]->argv)
					exit(0);
				exec_bin(korn->cmd[i]);
			}
			i++;
		}
		waiter(korn);
	}
}

/*  
** This func check if the given command is builtin or not
*/
int	is_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->name, "cd", 2) == 0)
		return (2);
	if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		return (3);
	if (ft_strncmp(cmd->name, "export", 6) == 0)
		return (4);
	if (ft_strncmp(cmd->name, "unset", 5) == 0)
		return (5);
	if (ft_strncmp(cmd->name, "env", 3) == 0)	
		return (6);
	if (ft_strncmp(cmd->name, "exit", 4) == 0)
		return (7);
	return (0);
}

/*  
** This func executes the builtin commands
*/
int	exec_(t_cmd *cmd, t_korn *korn, int command)
{
	if (command == 1)
		return (echo_(cmd));
	if (command == 2)
		return (cd_(cmd->argv[1], korn->env_head));
	if (command == 3)
		return (pwd_(korn));
	if (command == 4)
	{
		if (cmd->argc == 1)
			return (export_p(cmd->output, korn->env_head));
		else
			return (export_v(cmd->argv, korn->env_head));
	}
	if (command == 5)
		return (unset(korn));
	if (command == 6)
		return (env_(korn, cmd));
	if (command == 7)
		return (ft_exit(korn, cmd));
	return (0);
}

/*
** Takes the command and decides, if it's 
** builtin or not - and executes it as
** needed FIXME: Need to check for stupid inputs like - EcHo etc. 
*/
int	cmd_switch(t_cmd *cmd, t_korn *korn)
{
	int		command;
	int		ret;

	command = is_builtin(cmd);
	if (command == 0)
	{	
		if (!guns_n_roses(cmd->name))
			check_bin(cmd, korn);
		exec_bin(cmd);
		ret = g_sig.exit_status;
	}
	else
		ret = exec_(cmd, korn, command);
	return (ret);
}

/*  
** Checks if given command can be found in Paths or not
*/
int	check_bin(t_cmd *cmd, t_korn *korn)
{
	char	**paths;
	int		i;
	char	*final_path;

	i = 0;
	paths = ft_split(get_value("PATH", korn->env_head), ':');
	while (paths[i])
	{
		final_path = ft_strjoin3(paths[i], "/", cmd->name);
		if (access(final_path, F_OK) == 0)
			break ;
		free(final_path);
		++i;
	}
	if (!final_path)
		return (127);
	else
		cmd->path = final_path;
	return (0);
}

/*
** 		--- Waits for child processes ---
*/
void	waiter(t_korn *korn)
{
	int	i;
	int	stat;

	i = 0;
	while (i < korn->cmd_count)
	{
		wait(&stat);
		g_sig.exit_status = WEXITSTATUS(stat); // FIXME: needs improvements if p1 = 2; p2 = 0 -> should be 2
		i++;
	}
}
