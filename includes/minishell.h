#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
    char        *name;
    char        *data;
    struct      s_env *next;
}        t_env;

typedef struct  s_gehenna
{
    t_env *env_head;

}               t_gehenna;

void        data_init(t_gehenna **gehenna);
t_env       *env_keeper(char **env);

#endif