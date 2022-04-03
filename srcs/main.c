#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_korn		*korn;
	// t_env		*track;
	
	print_welcome_message();
	(void)argc;
	(void)argv;
	data_init(&korn);
	korn->env_head = env_keeper(env);
	// track = korn->env_head;

	t_cmd	*cmd = malloc(sizeof(t_cmd));
	cmd->args = malloc(sizeof(char *) * 2);
	cmd->args = "Hello my friend";
	cmd->output = 1;
	cmd->argc = 1;
	cmd->argv = ft_calloc(1, sizeof(char *) * 2);
	cmd->argv = &cmd->args;
	// ft_echo(cmd);

	show_prompt();
	return (0);
}

/* 
** Shows the prompt via readline
*/
char	*show_prompt(void)
{
	char	*line;

	while (1)
	{
		run_signals(1);
		line = readline(MAGENTA"AvôeL> "WHITE);
		if (!line)
			run_signals(3);
		else if (*line == '\0')
			free(line);
		else
		{
			if (ft_strlen(line) == 0)
				continue ;
			add_history(line);
		}
	}
	return (line);
}

/* 
** initialize main data structure 
*/
void	data_init(t_korn **korn)
{
	g_sig.exit_status = 0;
	*korn = (t_korn *)malloc(sizeof(t_korn));
	(*korn)->env_head = NULL;
}
