#include "../includes/minishell.h"

/*  
** This func check if the given command is builtin or not
*/
int		is_builtin(t_cmd *cmd)
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
int		exec_(t_cmd *cmd, t_korn *korn, int command)
{
	if (command == 1)
		return (ft_echo(cmd));
	if (command == 2)
		return (ft_cd(cmd->args, korn->env_head));
	if (command == 3)
		return (pwd(korn));
	if (command == 4)
		return (export(cmd->output, korn->env_head));
	if (command == 5)
		return (unset(korn));
	if (command == 6)
		return (env(korn));
	if (command == 7)
		return (ft_exit(korn, cmd));
	return (0);
}

/*
** Checks if there's a SLASH in command name or not
** ./a.out - returns TRUE (1)
** mkdir - returns FALSE (0)
*/
int	guns_n_roses(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (name[i] == '/')
			return (TRUE);
		++i;
	}
	return (FALSE);
}

/*
** Takes the command and decides, if it's 
** builtin or not - and executes it as
** needed
*/
int		cmd_switch(t_cmd *cmd, t_korn *korn)
{
	int		command;
	int		ret;

	command = is_builtin(cmd);
	if (command == 0)
	{	
		if (!guns_n_roses(cmd->name))
			check_bin(cmd, korn);
		ret = exec_bin(cmd);
	}
	else
		ret = exec_(cmd, korn, command);
	return ret;
}

/*  
** Checks if given command can be found in Paths or not
*/
int		check_bin(t_cmd *cmd, t_korn *korn)
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
			break;
		free(final_path);
		++i;
	}
	if (!final_path)
		return (127);
	else
	{
		ft_bzero(cmd->name, ft_strlen(cmd->name));
		cmd->name = final_path;
	}
	return (0);
}

// int	exec_bin(t_cmd *cmd)
// {
// 	int		pid;

// 	pid = fork();

// }
