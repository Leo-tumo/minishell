#include "../includes/minishell.h"

/*  
**  echo "$unknown_var" => '\n'
**  echo -n "$unknown_var" => 
**  echo xcho => xcho
**  echo $HOME =>  /Users/letumany
**  echo '$HOME' => $HOME
*/
int	echo_(t_cmd *cmd)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (cmd->argc > 1)
	{
		while (cmd->argv[i] && ft_strcmp(cmd->argv[i], "-n") == 0)
		{
			flag = 1;
			i++;
		}
		while (cmd->argv[i])
		{
			ft_putstr_fd(cmd->argv[i], 1);
			if (cmd->argv[i + 1] && cmd->argv[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
