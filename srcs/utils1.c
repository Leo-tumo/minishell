#include "../includes/minishell.h"

void	fill(char **to, char *from)
{
	int		len_from;
	int		len_to;
	char	*tmp;
	int		i;

	i = -1;
	tmp = *to;
	len_to = ft_strlen(*to);
	len_from = ft_strlen(from);
	while (++i < len_from)
	{
		*tmp = *from;
		++tmp;
		++from;
	}
	while (++i < len_to)
	{
		*tmp = '\0';
		++tmp;
	}
}

char	**first_step(char *str)
{
	char	**ret;
	char	*tmp1;
	int		i;

	i = -1;
	ret = ft_split(str, '|');
	while (ret[++i] != NULL)
	{
		tmp1 = ft_strtrim(ret[i], " ");
		free(ret[i]);
		ret[i] = tmp1;
		// free(tmp1);
	}
	return (ret);
}

int	line_count(char **splitted)
{
	int	i;	
	int	lines;

	i = -1;
	lines = 0;
	while (splitted[++i] != NULL)
		++lines;
	return (lines);
}
