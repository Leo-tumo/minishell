/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:52:50 by letumany          #+#    #+#             */
/*   Updated: 2022/04/15 14:55:52 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			ft_putstr_fd(cmd->argv[i], cmd->output);
			if (cmd->argv[i + 1] && cmd->argv[i][0] != '\0')
				write(cmd->output, " ", 1);
			i++;
		}
	}
	if (flag == 0)
		write(cmd->output, "\n", 1);
	g_sig.exit_status = 0;
	return (0);
}
