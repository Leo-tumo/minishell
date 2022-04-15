/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:38 by letumany          #+#    #+#             */
/*   Updated: 2022/04/15 15:01:39 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_korn		*korn;

	// print_welcome_message();
	(void)argc;
	(void)argv;
	data_init(&korn);
	korn->env_head = env_keeper(env);
	shlvl_(&korn->env_head);
	// show_prompt(korn);
	korn->cmd_count = 2;
	korn->cmd = malloc(sizeof(t_cmd) * 2);
	korn->child = malloc(sizeof(pid_t) * 2);
	korn->cmd[0].argv = ft_split("echo Hi mum", ' ');
	korn->cmd[0].argv[4] = NULL;
	korn->cmd[0].name = korn->cmd[0].argv[0];
	korn->cmd[0].input = 0;
	korn->cmd[1].argv = ft_split("cat -n", ' ');
	korn->cmd[1].argv[3] = NULL;
	korn->cmd[1].name = korn->cmd[1].argv[0];
	korn->cmd[1].id = 0;
	korn->cmd[1].output = 1;
	korn->cmd[1].input = 0;
	korn->cmd[0].output = 1;
	korn->cmd[0].argc = 2;
	pi_open(korn);
	incubator(korn);
	return (0);
}

/* 
** 	--- initialize main data structure
** 	--- It's just for the start 
*/
void	data_init(t_korn *korn)
{
	g_sig.exit_status = 0;
	korn = (t_korn *)malloc(sizeof(t_korn));
	korn->child = malloc(sizeof(pid_t));
	korn->cmd_count = 0;
	korn->heredoc_count = 0;
	korn->env_head = NULL;
	korn->cmd = NULL;
}
