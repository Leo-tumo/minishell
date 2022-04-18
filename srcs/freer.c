/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:58:54 by letumany          #+#    #+#             */
/*   Updated: 2022/04/18 20:53:21 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free2(char **s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		++i;
	}
}

void	free_cmds(t_korn *korn)
{
	int	i;

	i = 0;
	while (i < korn->cmd_count)
	{
		if (korn->cmd[i].name)
			free(korn->cmd[i].name);
		if (korn->cmd[i].path)
			free(korn->cmd[i].path);
		if (korn->cmd[i].argv[0])
			free2(korn->cmd[i].argv);
		if (korn->cmd[i].infile[0])
			free2(korn->cmd[i].infile);
		if (korn->cmd[i].outfile[0])
			free2(korn->cmd[i].outfile);
		if (korn->cmd[i].quote_flags)
			free(korn->cmd[i].quote_flags);
		free(&korn->cmd[i]);
		++i;
	}
}

/*
** 		deletes env struct
*/
void	delete_env(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		if (current->data)
			free(current->data);
		free(current);
		current = next;
	}
	*head = NULL;
}

/*
**	--- Frees everything freeable if kill is 1 	---
**	--- it frees env and korn itself. else -   	---
**	--- frees current input's commands			---
*/
void	free_root(t_korn *korn, int kill)
{
	if (korn->delimiters[0])
		free2(korn->delimiters);
	if (korn->cmd)
		free_cmds(korn);
	if (korn->child)
		free(korn->child);
	if (kill)
	{
		delete_env(&korn->env_head);
		free(korn);
	}
}

/* 
** -- Frees one cmd ---
 */
void	free_cmd(t_cmd *cmd)
{
	if (cmd->name)
			free(cmd->name);
	if (cmd->path)
		free(cmd->path);
	if (cmd->argv[0])
		free2(cmd->argv);
	if (cmd->infile[0])
		free2(cmd->infile);
	if (cmd->outfile[0])
		free2(cmd->outfile);
	if (cmd->quote_flags)
		free(cmd->quote_flags);
	free(cmd);
}
