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
// int		exec_(t_cmd *cmd, t_env *env, int command)
// {
// 	if (command == 1)
// 		return (echo(cmd, env));
// 	if (command == 2)
// 		return (ft_cd(cmd->args, env));
// 	if (command == 3)
// 		return (pwd(env));
// 	if (command == 4)
// 		return (export(env));
// 	if (command == 5)
// 		return (unset(cmd->args, env));
// 	if (command == 6)
// 		return (env(env));
// 	if (command == 7)
// 		return (exit(0));
// 	return (0);
// }
