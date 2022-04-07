#include "../includes/minishell.h"

void	init(t_cmd *c, char *str, t_korn *korn)
{
	c->infile_count = 0;
	c->outfile_count = 0;
	c->output_index = 0;
	c->input_index = 0;
	c->output_flag = get_output_flag(str);
	c->infile = input_redirs(str, &c->infile_count, korn);
	c->outfile = output_redirs(str, &c->outfile_count);
	c->input = 0;
	c->output = 1;
	// c->argument = NULL;
	c->name = NULL;
}

t_cmd	command_init(char *str, t_korn *korn)
{
	int		i;
	t_cmd	c;

	i = -1;
	init(&c, str, korn);
	while (str[++i])
	{
		if (ft_ispace(str[i]))
			continue ;
		else if (str[i] == '>')
			i = parse_output(str, i, &c);
		else if (str[i] == '<')
			i = parse_input(str, i, &c, korn);
	}
	return (c);
}

t_cmd	*t_cmd_init(char **splitted, t_korn **korn)
{
	int		i;
	t_cmd	*ret;

	i = -1;
	ret = (t_cmd *)malloc(((*korn)->cmd_count + 1) * sizeof(t_cmd));
	while (++i < (*korn)->cmd_count)
	{
		ret[i] = command_init(splitted[i], (*korn));
		print_struct(ret[i]);
	}
	return (ret);
}

void	parse(char *str, t_korn **korn)
{
	char	**splitted;

	splitted = first_step(str);
	(*korn)->cmd_count = line_count(splitted);
	(*korn)->cmd = t_cmd_init(splitted, korn);
	free(splitted);
}
