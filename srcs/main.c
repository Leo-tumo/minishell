#include "../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_korn		*korn; 

	print_welcome_message();
	(void)argc;
	(void)argv;
	data_init(&korn);
	korn->env_head = env_keeper(env);
	shlvl_(&korn->env_head);
	show_prompt(korn);
	return (0);
}

/* 
** initialize main data structure 
*/
void	data_init(t_korn **korn)
{
	g_sig.exit_status = 0;
	*korn = (t_korn *)malloc(sizeof(t_korn));
	(*korn)->env_head = NULL;
	(*korn)->cmd = NULL;
}
