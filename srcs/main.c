#include "../includes/minishell.h"

int main(int argc, char **argv, char **env)
{
        t_korn   *korn;
        t_env       *track;
        (void)argc;
        (void)argv;

        data_init(&korn);
        korn->env_head = env_keeper(env);
        track = korn->env_head;
        while(track->next != NULL)
        {
            if (ft_strncmp(track->name, "USER", 3) == 0)
                printf("%s\n", track->data);
            track = track->next;
        }
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
