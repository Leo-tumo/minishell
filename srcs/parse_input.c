#include "../includes/minishell.h"

int	parse_input(char *str, int i, t_cmd *c)
{
	int		k;
	char	*filename;

	k = i;
	filename = NULL;
	if (str[k + 1] && str[k + 1] == '<' && ++k)
		heredoc();
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
