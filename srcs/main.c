#include "../includes/minishell.h"
t_env    *env_keeper(char **env);

int main(int argc, char **argv, char **env)
{
    t_gehenna *gehenna;

    data_init(&gehenna);
    (void)argc;
    (void)argv;
    gehenna->env_head = env_keeper(env);
   
    while (1)
    {
        int fd = open("/dev/tty", O_RDWR);
        printf("%s\n",ttyname(fd));
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