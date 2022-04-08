#include "../includes/minishell.h" 

void	fork_count(t_korn *korn)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (i < korn->cmd_count)
	{
		if (korn->cmd[i].id == 0)
			ret++;	
		++i;
	}
	korn->fork_count = ret;
}

/*  
** This func check if the given command is builtin or not
**    Echo, Pwd & Env can have upper or lower case
*/
int	is_builtin(t_cmd cmd)
{
	if (ft_strncmp(lower_(cmd.name), "echo", 4) == 0)
		return (1);
	if (ft_strncmp(cmd.name, "cd", 2) == 0)
		return (2);
	if (ft_strncmp(lower_(cmd.name), "pwd", 3) == 0)
		return (3);
	if (ft_strncmp(cmd.name, "export", 6) == 0)
		return (4);
	if (ft_strncmp(cmd.name, "unset", 5) == 0)
		return (5);
	if (ft_strncmp(lower_(cmd.name), "env", 3) == 0)	
		return (6);
	if (ft_strncmp(cmd.name, "exit", 4) == 0)
		return (7);
	return (0);
}

/*  
** Checks if given command can be found in Paths or not
*/
int	pathfinder(t_cmd *cmd, t_korn *korn)
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
	{
		printf("bash: %s: command not found\n", cmd->name);
		return (127);
	}
	else
		cmd->path = final_path;
	free2(paths);
	return (0);
}
