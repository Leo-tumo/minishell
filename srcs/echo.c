#include "../includes/minishell.h"

/*  
** This is the pure echo command
** it parses everything and executes 
** 'echo' command with ready arguments
*/
int	ft_echo(t_cmd *cmd)
{
	int		i;
	char	*arg;
	int		flag;

	flag = 0;
	arg = NULL;
	i = 0;
	while (cmd->argv[i])
	{
		while (cmd->argv[i][0] == '-' && cmd->argv[i][1] == 'n' && !cmd->argv[i][2])
		{
			flag = 1;
			++i;
		}
		if (!arg && cmd->argv[i])
			arg = cmd->argv[i];
		else if(cmd->argv[i] && cmd->argv[i][0] != '\0')
			arg = ft_strjoin3(arg, " ", cmd->argv[i]);
		++i;
		printf("111 === %s\n", arg);
	}
	return (echo(&arg, cmd->output, flag, 1));
}

/*  
**  echo "$unknown_var" => '\n'
**  echo -n "$unknown_var" => 
**  echo xcho => xcho
**  echo $HOME =>  /Users/letumany
**  echo '$HOME' => $HOME
*/
int	echo(char **str, int fd, int flag, int argc)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 0;
	while (i < argc)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			ret += write(fd, &str[i][j], 1);
			++j;
		}
		if (i != argc - 1)
			ret += write(fd, " ", 1);
		++i;
	}
	if (flag == FALSE)
		write (fd, "\n", 1);
	free(str[0]);
	return (ret);
}
