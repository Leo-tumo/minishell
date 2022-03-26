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
# define TRUE 1
# define FALSE 0


/*  
** Bash errors
*/

# define COMMAND_NOT_FOUND 127 // command not found
# define PERMISSION_DENIED 126 // command found, but ain't executable

/*  
** Struct for command
*/

typedef struct s_cmd
{
	char		*name; // command name - ex. echo, cd, yes, tee, cal etc...
	char		*path;
	char		*args; // not sure yet for argument to use char * or char **
	char		**argv; // temporary maybe ....
	int			argc; // argument count
	int			input;
	int			output;
	int			flag; // 0 = other, 1 = echo, 2 = cd, 3 = pwd, 4 = export, 5 = unset, 6 = env, 7 = exit
	int			e_flag; // for echo command 0 = no flag, 1 = -n
}			t_cmd;

/*  
* This struck keeps 'env' variables
*/
typedef struct s_env
{
	char			*name;
	char			*data;
	int				is_exported;
	struct s_env	*next;
}				t_env;

/*  
** This is the main struct, maybe it'll turn to global
** and the name is too good 🤘🏻
** out => redirection output fd
** in  <= redirection input fd
*/
typedef struct s_korn
{
	t_env	*env_head;	// head of env variables
	int		out;
	int		in;
	int		argc;
	char	**argv;		
	int		x_st;		// exit status aka '$?'
}			t_korn;

void		data_init(t_korn **korn);
t_env		*env_keeper(char **env);
int			check_bin(t_cmd *cmd, t_korn *korn);

/*  
** util functions
*/
char		**env_split(char *str);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
void    	free_cmd(t_cmd *cmd);
int			check_bin(t_cmd *cmd, t_korn *korn);



/*  
** builtins and their utils
*/
int			is_valid_name(char *str);
int			env(t_korn *korn);
int			pwd(t_korn *korn);
int			ft_cd(char *path, t_env *head);
int			unset(t_korn *korn);
int			export(int fd, t_env *env);
int			export_(char**s, t_env *head);
int			export_append(char *s);
int			check_value(char *s);
int			check_existance(char *s, t_env *head);
char		*remove_plus_sign(char *s);
void		renew_var(char *new_var, int append, int has_value, t_env *head);
void		append_var(char *str, int flags, t_env *head, int is_exported);
char		*get_value(char *name, t_env *head);
int			echo(char **str, int fd, int flag, int argc);
int			ft_echo(t_cmd *cmd);
int  		ft_exit(t_korn *korn, t_cmd *cmd);




/* 
** file status checking functions 
*/
int			is_directory(char *path);
int			is_executable(char *path);
int			is_file(char *path);
int			is_link(char *path);
int			is_socket(char *path);
char		*show_prompt(void);
int			is_meta(char c);

#endif