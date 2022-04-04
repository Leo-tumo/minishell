#include "../includes/minishell.h"

char	*get_quoted_filename(char *str, int *i)
{
	int		k;
	int		len;
	char	quote;
	char	*name;

	quote = str[*i];
	len = 0;
	k = *i + 1;
	while (str[k] != quote)
	{
		++len;
		++k;
	}
	name = malloc(len + 1);
	ft_strlcpy(name, str + *i + 1, len + 1);
	*i += len + 1;
	return (name);
}

char	*get_filename(char *str, int *i)
{
	int		k;
	int		len;
	char	*name;

	k = *i;
	len = 0;
	while ((!ft_ispace(str[k]) && str[k] != '<' && str[k] != '>' ) && str[k])
	{
		++k;
		++len;
	}
	name = malloc(len + 1);
	ft_strlcpy(name, str + *i, len + 1);
	*i += len - 1;
	return (name);
}

char	*double_output(char *str, int *i)
{
	int		k;
	char	*name;

	k = *i + 1;
	name = NULL;
	while (str[++k])
	{
		if (ft_ispace(str[k]))
			continue ;
		else if (str[k] == '\'' || str[k] == '"')
		{
			name = get_quoted_filename(str, &k);
			break ;
		}
		else if (str[k] == '>' || str[k] == '<')
		{
			printf("double output syntax error, statusy piti lini 258\n");
			return (NULL);
		}
		else
		{
			name = get_filename(str, &k);
			break ;
		}
	}
	return (name);
}

int	parse_output(char *str, int i, t_cmd *c)
{
	int		k;
	char	*filename;

	k = i;
	filename = NULL;
	if (str[k + 1] && str[k + 1] == '>' && ++k)
		filename = double_output(str, &k);
	while (str[++k] != '\0')
	{
		if (ft_ispace(str[k]))
			continue ;
		else if (str[k] == '"' || str[k] == '\'')
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
	c->outfile[c->output_index] = malloc(ft_strlen(filename) + 1);
	fill(&c->outfile[c->output_index], filename);
	++c->output_index;
	return (k);
}


char **output_redirs(char *s, int *count)
{
    int     i;
    char    quote;
    char    **ret;
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
        if (s[i] == '>' && s[i + 1] && s[i + 1] == '>')
            ++i;
        if (s[i] == '>' && s[i + 1] && s[i + 1] != '>')
            ++(*count);
    }
    ret = malloc(sizeof(char *) * (*count + 1));
    return (ret);
}

int get_output_flag(char *str)
{
    int l;
    // int flag;

    // flag = 0;
    l = ft_strlen(str);
    while (--l > 0)
    {
        if (str[l] == '>')
        {
            if (str[l - 1] && str[l - 1] == '>')
                return (O_APPEND);
            return (O_TRUNC);
        }
    }
    return (0);
}
