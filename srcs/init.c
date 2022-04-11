#include "../includes/minishell.h"

int get_argc(char *str)
{
 int  i;
 int  count;
 char quote;

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
	else if (str[i] == '>' || str[i] == '<')
	{
	 ++i;
	 while (ft_ispace(str[i]))
		++i;
	 while (!ft_ispace(str[i]))
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

void init(t_cmd *c, char *str, t_korn *korn)
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
 c->argc = get_argc(str);
 c->argv = malloc(sizeof(char *) * (c->argc + 1));
 c->arg_index = 0;
 c->name = NULL;
 c->quote_flags = ft_calloc(sizeof(int), (c->argc + 1));
}

int treat_quote(char *str, int i, t_cmd *cmd)
{
 char quote;

 quote = str[i++];
 if (quote == '\'')
 {
	cmd->quote_flags[cmd->arg_index] = 1;
	while (str[i] != quote)
	 i += char_join(str[i], &cmd->argv[cmd->arg_index]);
 }
 else if (quote == '"')
 {
	cmd->quote_flags[cmd->arg_index] = 2;
	while (str[i] != quote)
	 i += char_join(str[i], &cmd->argv[cmd->arg_index]);
 }
 return (i + 1);
}

int len_4_cmd(char *str, int i)
{
 int  len;
 char quote;

 len = 0;
 while (str[i] && !ft_ispace(str[i]))
 {
	// printf("4%c\n", str[i]);
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
 // printf("LEN = %d\n", len);
 return (len);
}

char *ch_join(char c, char *s)
{
 int  i;
 char *str;

 str = NULL;
 if (!(s))
 {
	str = malloc(2);
	str[0] = c;
	str[1] = '\0';
	return (str);
 }
 printf("STRING === %s\n", s); //FIXME:
 str = (char *)malloc(ft_strlen(s) + 2);
 i = 0;
 while(s[i])
 {
	str[i] = s[i];
	++i;
 }
 str[i] = c;
 str[i + 1] = '\0';
 free (s);
 return (str);
}

int parse_command(char *str, int i, t_cmd *cmd)
{
 	cmd->argv[cmd->arg_index] = malloc(len_4_cmd(str, i) + 1);
 	while (str[i] && !ft_ispace(str[i]))
 	{
		if ((str[i] == '\'' || str[i] == '"') && str[i + 1] != '\0')
	 		i = treat_quote(str, i, cmd);
		cmd->argv[cmd->arg_index] = ch_join(str[i], cmd->argv[cmd->arg_index]);
		++i;
 	} 
 	printf("%d\n", cmd->arg_index);
 	printf("S = %s\n", cmd->argv[cmd->arg_index]);
 	++cmd->arg_index;
 	return (i);
}

t_cmd	*command_init(char *str, t_korn *korn)
{
	int 	i;
 	t_cmd	*c;

 	i = 0;
	 c = NULL;
 	init(c, str, korn);
	c = malloc(sizeof(t_cmd)); 
 	while (str[i])
 	{
		if (ft_ispace(str[i]))
		{
			++i;
			continue ;
		}
		else if (str[i] == '>')
			i = parse_output(str, i, c);
		else if (str[i] == '<')
			i = parse_input(str, i, c);
		else
		{
			i = parse_command(str, i, c);
		// break ;
		}
		++i;
 	}
 	return (c);
}


t_cmd	*t_cmd_init(char **splitted, t_korn **korn)
{
	int		i;
	t_cmd	**ret;

	i = -1;
	ret = (t_cmd **)malloc(((*korn)->cmd_count + 1) * sizeof(t_cmd));
	while (++i < (*korn)->cmd_count)
	{
		ret[i] = command_init(splitted[i], (*korn));
		print_struct(*ret[i]);
	}
	return (*ret);
}

void	parse(char *str, t_korn **korn)
{
	char	**splitted;

	splitted = first_step(str);
	(*korn)->cmd_count = line_count(splitted);
	(*korn)->cmd = t_cmd_init(splitted, korn);
	free(splitted);
}
