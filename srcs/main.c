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
	// show_prompt(korn);
	pid_t	SIL = fork();
	if (SIL == 0)
	{
		export_v(ft_split("export a=thisissparta", ' '), &korn->env_head);
	}
	else
	{
		export_p(1, &korn->env_head);
		wait(NULL);
	}
	return (0);
}

/* 
** initialize main data structure 
*/
void	data_init(t_korn **korn)//add korn initialization
{
	g_sig.exit_status = 0;
	*korn = (t_korn *)malloc(sizeof(t_korn));
	(*korn)->env_head = NULL;
	(*korn)->cmd = NULL;
}
