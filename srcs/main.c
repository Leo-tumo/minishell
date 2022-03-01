#include "../includes/minishell.h"
#include <sys/stat.h>

int main(int argc, char **argv, char **env)
{
    char fd[10] = "myfile.txt";
    struct stat *buf;

    buf = malloc(sizeof(struct stat));

    stat(fd, buf);
    printf("%d\n",buf->st_mode);

    free(buf);

    t_gehenna *gehenna;

    data_init(&gehenna);
    (void)argc;
    (void)argv;
    // printf("%s\n", getenv("PWD"));
    gehenna->env_head = env_keeper(env);
    while (1)
    {
        char *line = readline("AvôeL> ");
        if (!line)
            break;
        if (ft_strlen(line) == 0)
            continue;
        add_history(line);
        // char **args = split_line(line);
        // int status = execute(args);
        free(line);
        // free(args);
    }
    return (0);
}

/* 
** Shows the content of chosen directory
*/
int mini_ls(char *path)
{
    struct dirent   *de;
    DIR             *dr;

    dr = opendir(path);
    if (dr == NULL) 
    {
        perror("Could not open current directory");
        return 0;
    }
  
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
  
    closedir(dr);    
    return 0;
}

/* 
** keep environment variables in a linked list
*/
t_env*    env_keeper(char **env)
{
    t_env *head;
    t_env *current = NULL;
    t_env *temp = NULL;
    int i = 0;
    head = NULL;

    while (env[i])
    {
        temp = (t_env*)malloc(sizeof(t_env));
        temp->data = ft_strdup(env[i]);
        temp->next = NULL;
        if (!head)
            head = temp;
        else
            current->next = temp;
        current = temp;
        i++;
    }
    return (head);
}

/* 
** initialize main data structure 
*/
void    data_init(t_gehenna **gehenna)
{
    *gehenna = (t_gehenna*)malloc(sizeof(t_gehenna));
    (*gehenna)->env_head = NULL;
}
