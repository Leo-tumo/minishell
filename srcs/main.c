#include "../includes/minishell.h"

extern  char    **environ;
int main(int argc, char **argv, char **env)
{
        char    **s = environ;
        for(; *s; s++){printf("--%s\n", *s);}
        printf("%s\n", getenv("OLDWD"));
        t_korn   *korn;
        t_env       *track = NULL;
        (void)argc;
        (void)argv;

        data_init(&korn);
        korn->env_head = env_keeper(env);
        track = korn->env_head;
        int fd = open("new.txt", O_RDWR | O_CREAT, 0x755);
        // export(fd, track);
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
