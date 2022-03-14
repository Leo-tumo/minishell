#include "../includes/minishell.h"

extern  char    **environ;
int main(int argc, char **argv, char **env)
{
        t_korn   *korn;
        t_env       *track = NULL;
        (void)argc;
        (void)argv;

		char	**test = calloc(2, 50);
		test[0] = "new_var=8137";
		test[1] = "next_var+=fhauf8";
        data_init(&korn);
        korn->env_head = env_keeper(env);
        track = korn->env_head;
        int fd = open("new.txt", O_RDWR | O_CREAT, 0x755);
		export_(test, track);
        export(1, track);
        close(fd);
        show_prompt();
    return (0);
}


/* 
** Shows the prompt via readline
*/
char    *show_prompt(void)
{
    char    *line;
    while (1)
    {
        line = readline("AvôeL> ");
        if (!line)
            break;
        if (ft_strlen(line) == 0)
            continue;
        add_history(line);
        free(line);
    }
    return line;
}


/* 
** initialize main data structure 
*/
void    data_init(t_korn **korn)
{
    *korn = (t_korn*)malloc(sizeof(t_korn));
    (*korn)->env_head = NULL;
}
