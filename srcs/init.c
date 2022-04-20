/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:11:16 by amidoyan          #+#    #+#             */
/*   Updated: 2022/04/20 17:22:40 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_4_cmd(char *str, int i)
{
	int		len;
	char	quote;

	len = 0;
	while (str[i] && !ft_ispace(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			++i;
			while (str[++i] != quote)
				++len;
		}
		else
			++len;
		++i;
	}
	return (len);
}

int	parse_command(char *str, int i, t_cmd *cmd)
{
	int		j;

	j = 0;
	cmd->argv[cmd->arg_index] = malloc(len_4_cmd(str, i) + 1);
	while (str[i] && !ft_ispace(str[i]) && str[i] != '>' && str[i]!= '<')
	{
		if (str[i] == '\'' || str[i] == '"')
			i = treat_quote(str, i, &j, cmd) + 1;
		else
		{
			cmd->argv[cmd->arg_index][j] = str[i];
			++i;
			++j;
		}
	}
	cmd->name = cmd->argv[0];
	++cmd->arg_index;
	return (i - 1);
}

int	syntax_error_check(char *str)
{
	int		i;
	char	symbol;
	int		flag;

	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			flag = 1;
			symbol = str[i];
			while (str[++i] && (str[i] != symbol))
				continue ;
			if (str[i] == symbol)
				flag = 0;
		}
		if (str[i] == '|')
		{
			while (str[++i] && str[i] != '|')
				++i;
			if (str[i] == '|')
				return (printf("bash: Syntax Error\n"));
		}
	}
	if (flag == 1)
		return (printf("bash: Syntax Error\n"));
	return (0);
}

int	get_argc(char *str)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && str[++i])
		{
			quote = str[i - 1];
			while (str[i] != quote)
				++i;
		}
		else if (str[i] && (str[i] == '>' || str[i] == '<'))
		{
			++i;
			while (ft_ispace(str[i]))
				++i;
			while (str[i] && !ft_ispace(str[i]))
			{
				if ((str[i] == '\'' || str[i] == '"') && str[++i])
				{
					quote = str[i - 1];
					while (str[i] != quote)
						++i;
				}
				++i;
			}
		}
		if (!ft_ispace(str[i]) && (ft_ispace(str[i + 1]) || str[i + 1] == '\0'))
			++count;
		++i;
	}
	return (count);
}

char	**heredoc_zibil(int *c, char *str)
{
	int		i;
	char	quote;
	char	**ret;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
			while (str[++i] && str[i] != quote)
				continue ;
		}
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<')
		{
			++i;
			++*c;
		}		
	}
	ret = malloc(sizeof(char *) * ((*c) + 1));
	ret[*c] = NULL;
	return (ret);
}

t_doc	*heredoc_init(char *str)
{
	t_doc	*tmp;

	tmp = malloc(sizeof(t_doc));
	tmp->d_q = 0;
	tmp->heredoc_count = 0;
	tmp->delimiters = heredoc_zibil(&tmp->heredoc_count, str);
	tmp->status = 0;
	tmp->d_i = 0;
	return (tmp);
}

void	init(t_cmd *c, char *str)
{
	c->infile_count = 0;
	c->outfile_count = 0;
	c->output_index = 0;
	c->input_index = 0;
	c->name = NULL;
	c->path = NULL;
	c->output_flag = get_output_flag(str);
	c->doc = heredoc_init(str);
	c->infile = input_redirs(str, &c->infile_count, c);
	c->outfile = output_redirs(str, &c->outfile_count);
	c->input = 0;
	c->output = 1;
	c->argc = get_argc(str);
	c->argv = calloc(sizeof(char *), (c->argc + 1));
	c->arg_index = 0;
	c->quote_flags = ft_calloc(sizeof(int), (c->argc + 1));
}

int	treat_quote(char *str, int i, int *j, t_cmd *cmd)
{
	char	quote;

	quote = str[i++];
	if (quote == '\'')
	{
		cmd->quote_flags[cmd->arg_index] = 1;
		while (str[i] != quote)
		{
			cmd->argv[cmd->arg_index][*j] = str[i];
			++i;
			++*j;
		}
	}
	else if (quote == '"')
	{
		cmd->quote_flags[cmd->arg_index] = 2;
		while (str[i] && (str[i] != quote))
		{
			cmd->argv[cmd->arg_index][*j] = str[i];
			++i;
			++*j;
		}
	}
	return (i);
}

t_cmd	command_init(char *str)
{
	int		i;
	t_cmd	c;

	i = -1;
	init(&c, str);
	while (str[++i] && i < (int)ft_strlen(str))
	{
		if (ft_ispace(str[i]))
			continue ;
		else if (str[i] == '>')
			i = parse_output(str, i, &c);
		else if (str[i] == '<')
			i = parse_input(str, i, &c);
		else
			i = parse_command(str, i, &c);
	}
	return (c);
}

void	check_outputs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (cmd->outfile[++i] && i < cmd->outfile_count)
	{
		fd = open(cmd->outfile[i], O_WRONLY | O_CREAT | cmd->output_flag);
		if (fd == -1)
		{
			cmd->output = -1;
			perror(ft_strjoin("bash: ", cmd->outfile[i]));
		}
		if (cmd->output != 1)
			close(cmd->output);
		cmd->output = fd;	
	}
}

void	check_inputs(t_cmd *cmd)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (cmd->infile[++i] && i < cmd->infile_count)
	{
		fd = open(cmd->infile[i], O_RDONLY);
		if (fd == -1)
		{
			cmd->input = -1;
			perror(ft_strjoin("bash: ", cmd->infile[i]));
			break ;
		}
		if (cmd->input != 0)
			close(cmd->input);
		cmd->input = fd;
	}
}

void	files_checker(t_cmd *cmd, int ac)
{
	int	i;

	i = -1;
	while (++i < ac)
	{
		if (cmd[i].infile_count > 0)
			check_inputs(&cmd[i]);
		if (cmd[i].outfile_count > 0)
			check_outputs(&cmd[i]);
	}
}

t_cmd	*t_cmd_init(char **splitted, t_korn **korn)
{
	int		i;
	t_cmd	*ret;

	i = -1;
	ret = (t_cmd *)calloc(((*korn)->cmd_count + 1), sizeof(t_cmd));
	while (++i < (*korn)->cmd_count)
	{
		ret[i] = command_init(splitted[i]);
		print_struct(ret[i]);
	}
	return (ret);
}

void	parse(char *str, t_korn **korn)
{
	char	**splitted;

	if (syntax_error_check(str))
		return ;
	splitted = first_step(str);
	(*korn)->cmd_count = line_count(splitted);
	(*korn)->cmd = t_cmd_init(splitted, korn);
	files_checker((*korn)->cmd, (*korn)->cmd_count);
	free(splitted);
}
