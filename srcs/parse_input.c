/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:01:52 by amidoyan          #+#    #+#             */
/*   Updated: 2022/04/16 11:05:53 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_input(char *str, int i, t_cmd *c)
{
	int		k;
	char	*filename;

	k = i;
	filename = NULL;
	if (str[k + 1] && str[k + 1] == '<' && ++k)
		printf("HEREDOC:)\n");
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
	c->infile[c->input_index] = ft_strdup(filename);
	++c->input_index;
	return (k);
}

char	**input_redirs(char *s, int *count, t_korn *korn)
{
	int		i;
	char	quote;
	char	**ret;

	i = -1;
	ret = NULL;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && s[++i])
		{
			quote = s[i - 1];
			while (s[i] != quote)
				++i;
		}
		if (s[i] == '<' && s[i + 1] && s[i + 1] == '<')
			here_doc(korn);
		else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
			++(*count);
	}
	ret = malloc(sizeof(char *) * (*count + 1));
	return (ret);
}
