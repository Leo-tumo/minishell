#include "../includes/minishell.h"

extern  char    **environ;

int main(int argc, char **argv, char **env)
{
        t_korn      *korn;
        t_env       *track;

        (void)argc;
        (void)argv;
        
        data_init(&korn);
        korn->env_head = env_keeper(env);
        track = korn->env_head;
        ft_cd("~-", track);
        // printf("%s\n", getcwd(NULL, 0));

        // show_prompt();
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
