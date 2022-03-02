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
		fill(&ret[i], tmp1);
		free(tmp1);
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

t_cmd	command_init(char *str)
{
	int		i;
	t_cmd	command;

	i = -1;
	while (str[++i])
	{
		if (ft_isspace(str[i]))
			continue ;
		else
		{
			if (str[i] == '>')
				i += input_redir_parse(str, &command);
			else if (str[i] == '<')
				i += output_redir_parse(str, &command);
			else
				i += command_parse(str, &command);
		}
	}
	return (command);
}

t_cmd	*t_cmd_init(char **splitted, int lines)
{
	t_cmd	*ret;
	int		i;

	i = -1;
	ret = (t_cmd *)malloc(lines * sizeof(t_cmd));
	while (++i < lines)
	{
		ret[i] = command_init(splitted[i]);
	}
}

void	parse(char *str)
{
	int		lines;
	char	**splitted;
	t_cmd	*line_commands;

	splitted = first_step(str);
	lines = line_count(splitted);
	line_commands = t_cmd_init(splitted, lines);
	free(splitted);
}

int	main(void)
{
	while (1)
	{
		char *str = readline("minihell $> ");
		parse(str);
		//rl_replace_line("How", 1);
	
		add_history(str);
		if (str[0] == '-')
			clear_history();
		free(str);
	}
}
