/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:11:08 by letumany          #+#    #+#             */
/*   Updated: 2022/04/20 17:11:09 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quoted_delim(char *str, int k)
{
	printf("MTA%d\n", k);
	while (str[k] && !ft_ispace(str[k]))
	{
		if (str[k] == '\'' || str[k] == '"')
			return (TRUE);
		++k;
	}
	return (FALSE);
}

int	delim_len(char *str, int k)
{
	int		len;
	char	quote;

	len = 0;
	while (str[k] && !ft_ispace(str[k]))
	{
		if (str[k] == '\'' || str[k] == '"')
		{
			quote = str[k];
			++k;
			while (str[k++] != quote)
				++len;
			++k;
		}
		if (ft_ispace(str[k]))
			break ;
		++len;
		++k;
	}
	return (len);
}

void	unqouted_delim(char **delim, int *k, char *str)
{
	int	i;

	i = *k;
	while ((!ft_ispace(str[i]) && str[i] != '<' && str[i] != '>' ) && str[i])
		++i;
	ft_strlcpy(*delim, str + *k, i - (*k) + 1);
	*k = i;
}

void	quoted_delim(char **delim, int *k, char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[*k] && !ft_ispace(str[*k]))
	{
		if (str[*k] == '\'' || str[*k] == '"')
		{
			quote = str[*k];
			++*k;
			while (str[*k] && str[*k] != quote)
			{
				(*delim)[i] = str[*k];
				++i;
				++*k;
			}
		}
		if (str[*k] == quote)
			++*k;
		(*delim)[i] = str[*k];
		++i;
		++*k;
	}	
}

char	*get_delim(char *delim, char *str, int *k, int status)
{
	delim = malloc(delim_len(str, *k) + 1);
	if (status == 0)
		unqouted_delim(&delim, k, str);
	else if (status == 1)
		quoted_delim(&delim, k, str);
	return (delim);
}

int	parse_heredoc(char *str, int k, t_cmd *c)
{
	char	*delim;

	delim = NULL;
	while (ft_ispace(str[k]))
		++k;
	if (check_quoted_delim(str, k))
		c->doc->d_q = 1;
	delim = get_delim(delim, str, &k, c->doc->d_q);
	c->doc->delimiters[c->doc->d_i] = malloc(ft_strlen(delim) + 1);
	fill(&c->doc->delimiters[c->doc->d_i++], delim);
	return (k);
}

int	parse_input(char *str, int i, t_cmd *c)
{
	int		k;
	char	*filename;

	k = i;
	filename = NULL;
	if (str[k + 1] && str[k + 1] == '<' && ++k)
		return (parse_heredoc(str, k + 1, c) - 1);
	while (str[++k])
	{
		if (ft_ispace(str[k]))
			continue ;
		else if (str[k] == '\'' || str[k] == '"')
		{
			filename = get_quoted_filename(str, &k);
			break ;
		}
		else if (str[k] == '>' || str[k] == '<')
		{
			printf("syntax error, statusy piti lini 258\n");
			return (k + 1);
		}
		else
		{
			filename = get_filename(str, &k);
			break ;
		}
	}
	c->infile[c->input_index] = malloc(ft_strlen(filename) + 1);
	fill(&c->infile[c->input_index], filename);
	++c->input_index;
	return (k);
}

char	**input_redirs(char *s, int *count, t_cmd *cmd)
{
	int		i;
	char	quote;
	char	**ret;

	i = -1;
	(void)cmd;
	ret = NULL;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && s[++i])
		{
			quote = s[i - 1];
			while (s[i] != quote)
				++i;
		}
		if (s[i] == '<' && s[i + 1] && s[i + 1] == '<' && s[i + 2])
			++i;
		else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
			++(*count);
	}
	ret = malloc(sizeof(char *) * (*count + 1));
	return (ret);
}
