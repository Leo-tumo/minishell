/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:56:36 by letumany          #+#    #+#             */
/*   Updated: 2022/04/16 11:04:02 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

/*  
** Frees cmd members and cmd, after execution
*/
int	free_n_exit(t_korn *korn, int exit_status)
{
	free_root(korn, 1);
	exit (exit_status);
}

/*  
** 		Checks if arg for exit is valid or not
** 		Only number ex. +389 -0 etc.
** 		Can't be bigger than MAX_LONG
*/
int	xarg_check(char *str)
{
	int64_t		i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		++i;
	if (ft_strlen(str) - i > 19)
		return (FALSE);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		++i;
	}
	i = ft_atoi(str);
	if (i > LLONG_MAX || i < LLONG_MIN
		|| (str[0] != '-' && i < 0) || (str[0] == '-' && i > 0))
		return (FALSE);
	return (TRUE);
}

/*  
** if no argument - exits with last exit status $?
** can take only 1 long long int argument. 
** if arg > 256 returns arg % 256
** if argument ain't numeric - exits and returns 2
** if it has many arguments - just returns error message and 1
*/
int	exit_(t_cmd *cmd, t_korn *korn)
{
	int	i;

	if (cmd->argc == 1)
		return (free_n_exit(korn, g_sig.exit_status));
	else if (xarg_check(cmd->argv[1]) == FALSE)
	{
		ft_putstr_fd("exit\nbash: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		i = 2;
		return (free_n_exit(korn, 2));
	}
	else if (cmd->argc > 2)
	{
		ft_putstr_fd("exit\n bash: exit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		i = (int)(ft_atoi(cmd->argv[1]) % 256);
		return (free_n_exit(korn, i));
	}
}
