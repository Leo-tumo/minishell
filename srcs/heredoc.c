/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:00:46 by letumany          #+#    #+#             */
/*   Updated: 2022/04/19 18:13:01 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*  
** 		 if string contains any '$' sign
**		returns -TRUE- else returns -FALSE-
*/
int	check_dollar_sign(char	*str)
{
	while (*str)
	{
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

/*  
** 	Replaces var name in heredoc with its value
*/
char	*replace_var(char *str, t_env *env)
{
	char	*ret;
	char	*var_name;

	ret = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			var_name = NULL;
			str++;
			if (ft_ispace(*str) || !*str)
				char_join('$', &ret);
			else if (*str == '?')
				str += char_join('0', &ret);
			else if (*str == '_' || ft_isalpha(*str))
				ret = repl_dollar(ret, &var_name, &str, env);
			else
				++str;
		}
		else
		{
			str += char_join(*str, &ret);
		}
	}
	return (ret);
}

/*  
** Actual heredoc is here, inside child process
*/
void	heredoc_child(t_korn *korn, int fd, char *delimiter, t_cmd *cmd)
{
	char	*buf;

	buf = readline("> ");
	while (buf)
	{
		g_sig.line++;
		if (cmd->doc->d_q && check_dollar_sign(buf))
			buf = replace_var(buf, korn->env_head);
		ft_putendl_fd(buf, fd);
		free(buf);
		buf = readline("> ");
		if (!ft_strcmp(buf, delimiter))
		{
			free(buf);
			exit(0);
		}
		if (!buf)
		{
			printf("bash: warning: here-document at line %d ", g_sig.line);
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
			exit(0);
		}
	}
}

/*  
** This is fake heredoc, in case of multiple heredocs 2🍕
*/
void	fake_heredoc(t_cmd *cmd, char *delimiter)
{
	char	*buf;

	cmd->doc->heredoc_count--;
	buf = readline("> ");
	while (ft_strcmp(buf, delimiter))
	{
		free(buf);
		buf = readline("> ");
		g_sig.line++;
		if (!buf)
		{
			printf("bash: warning: here-document at line %d ", g_sig.line);
			printf("delimited by end-of-file (wanted `%s')\n", delimiter);
			return ;
		}
	}
}

/*  
** This function allows us to get heredoc's output to STDIN
** if there are multiple heredocs, it fake them except the last one
*/
void	here_doc(t_korn *korn, t_cmd *cmd)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		run_signals(4);
		while (i + 1 < cmd->doc->heredoc_count)
			fake_heredoc(cmd, cmd->doc->delimiters[i++]);
		heredoc_child(korn, fd[1], cmd->doc->delimiters[i], cmd);
		close(fd[0]);
	}
	else
	{
		run_signals(1);
		cmd->input = fd[0];
		waitpid(pid, &g_sig.exit_status, WEXITSTATUS(g_sig.exit_status));
		close_2(fd);
	}
}
