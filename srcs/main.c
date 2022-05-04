/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:38 by letumany          #+#    #+#             */
/*   Updated: 2022/04/19 18:44:23 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_korn		*korn;

	print_welcome_message();
	(void)argc;
	(void)argv;
	data_init(&korn);
	korn->env_head = env_keeper(env);
	shlvl_(&korn->env_head);
	show_prompt(korn);
	return (0);
}

/* 
** 	--- initialize main data structure
** 	--- It's just for the start 
*/
void	data_init(t_korn **korn)
{
	g_sig.exit_status = 0;
	*korn = (t_korn *)malloc(sizeof(t_korn));
	(*korn)->child = malloc(sizeof(pid_t));
	(*korn)->cmd_count = 0;
	(*korn)->env_head = NULL;
	(*korn)->cmd = NULL;
}
