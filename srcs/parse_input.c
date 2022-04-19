#include "../includes/minishell.h"

int	check_quoted_delim(char *str, int k)
{
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
			break;
		++len;
		++k;
	}
	printf("LEN === %d\n", len);
	return (len);
}

int parse_heredoc(char *str, int k, t_cmd *c)
{
	while (ft_ispace(str[k]))
		++k;
	printf("SEG?%d\n", k);
	
	if (check_quoted_delim(str, k))
	{
		printf("NO\n");
		c->doc->d_q = 1;
	}
	printf("INDEX");
	printf("PLAYA PLAYA === %i\n", c->doc->d_i);
	c->doc->delimiters[c->doc->d_i] = malloc(delim_len(str, k) + 1);
	return (0);
		
}

int	parse_input(char *str, int i, t_cmd *c)
{
	int		k;
	char	*filename;

	
	k = i;
	filename = NULL;
	if (str[k + 1] && str[k + 1] == '<' && ++k)
	{
		printf("str[k] === %c &&  str[k + 1] === %c\n", str[k], str[k + 1]);
		printf("PARSE_I %d\n", k + 1);
		return(parse_heredoc(str, k + 1, c));
	}
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
		{
			++i;    //FIXME:
			cmd->doc->heredoc_count++;
		}
		else if (s[i] == '<' && s[i + 1] && s[i + 1] != '<')
			++(*count);
	}
	ret = malloc(sizeof(char *) * (*count + 1));
	return (ret);
}
