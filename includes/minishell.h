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
# include <sys/stat.h>

/*
* Sorry I love 🐍
*/
# define True 1
# define False 0

/*  
* This struck keeps 'env' variables
*/

typedef struct s_env
{
    char        *name;
    char        *data;
    struct      s_env *next;
}        t_env;

/*  
** This is the main struct, maybe it'll turn to global
** and the name is too good 🤘🏻
*/
typedef struct  s_korn
{
    t_env *env_head;

}               t_korn;

void        data_init(t_korn **korn);
t_env       *env_keeper(char **env);


/* 
** file status checking functions 
*/
int     is_directory(char *path);
int     is_executable(char *path);
int     is_file(char *path);
int     is_link(char *path);
int     is_socket(char *path);
char    *show_prompt(void);
int     is_meta(char c);

#endif