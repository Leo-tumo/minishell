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

# define MAGENTA "\001\033[1;35m\002"
# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;92m\002"
# define RED "\001\033[1;31m\002"

/*
* Sorry I love 🐍
*/
# define TRUE 1
# define FALSE 0

/*  
** Bash errors
*/
# define PERMISSION_DENIED 	126 // command found, but ain't executable
# define COMMAND_NOT_FOUND 	127 // command not found

/*  
** Struct for command
*/
typedef struct s_cmd
{
	char		*name; // command name - ex. echo, cd, yes, tee, cal etc...
	char		*path; // this is very important -> commands full path
	char		**argv; // needed for execve || can be replaced by ft_split(args, " "). Should include commans name
	int			argc; // argument count
	int			input;
	int			output;
	int			flag; // 0 = other, 1 = echo, 2 = cd, 3 = pwd, 4 = export, 5 = unset, 6 = env, 7 = exit
	char		**infile;
	int			infile_count;//? malloci hamar
	int			input_index;
	char		**outfile;
	int			outfile_count;//?malloci hamar
	int			output_flag; //O_TRUNC kam O_APPEND kaxvac outputi tipic
	int			output_index; //for the malloc in 2d output array
}			t_cmd;

/*  
** Yet the only global ✵
*/
typedef struct s_sig
{
	int		exit_status;
}		t_sig;

t_sig	g_sig; // exit status aka '$?'

/*  
* This struck keeps 'env' variables
*/
typedef struct s_env
{
	char			*name;
	char			*data;
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
	int		line; // counts lines for heredoc error message
	int		d_q; // if final delimiter is quoted = 1 else 0
	int		heredoc_count; // in case that there are many Speciall for 2🍕s
	char	**delimiters; // heredoc delimiters' gang ✵ - should replace t_doc linked list;
	t_env	*env_head;	// head of env variables
	int		cmd_count; // count of commands
	t_cmd	*cmd; // commands themself
	pid_t	*child; // pid array for processes
}			t_korn;

/* 
** 		---	Starters ---
*/
char		*show_prompt(t_korn *korn);
void		shlvl_(t_env *env, char **nv);
void		restore_prompt(int sig);
void		print_welcome_message(void);
void		data_init(t_korn **korn);
t_env		*env_keeper(char **env);
int			check_bin(t_cmd *cmd, t_korn *korn);
void		run_signals(int sig);
void		here_doc(t_korn *korn);
/*  
** util functions
*/
void		delete_var(t_env **head, char *key);
void		close_2(int *fd);
char		*repl_dollar(char *ret, char **var_name, char **str, t_env *env);
int			ft_strcmp(const char *s1, const char *s2);
int			char_join(char c, char **s1);
char		**env_split(char *str);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
void		free_cmd(t_cmd *cmd);
int			check_bin(t_cmd *cmd, t_korn *korn);
int			guns_n_roses(char *name);

/*  
** builtins and their utils
*/
int			is_valid_name(char *str);
int			env_(t_korn *korn, t_cmd *cmd);
int			pwd_(t_cmd cmd);
int			cd_(char *path, t_env *head);
int			unset_(t_korn *korn, t_cmd *cmd);
int			export_p(int fd, t_env *env);
int			export_v(char**s, t_env *head);
int			export_append(char *s);
int			check_value(char *s);
int			check_existance(char *s, t_env *head);
char		*remove_plus_sign(char *s);
void		renew_var(char *new_var, int append, int has_value, t_env *head);
void		append_var(char *str, int flags, t_env *head);
char		*get_value(char *name, t_env *head);
int			echo_(t_cmd *cmd);
int			ft_exit(t_korn *korn, t_cmd *cmd);

/* 
** file status checking functions 
*/
int			is_directory(char *path);
int			is_executable(char *path);
int			is_file(char *path);
int			is_link(char *path);
int			is_socket(char *path);
int			is_meta(char c);

/*
** AVO functions ⇣⇣
*/
int			ft_ispace(int c);
char		**first_step(char *str);
char		*get_quoted_filename(char *str, int *i);
char		*get_filename(char *str, int *i);
char		*double_output(char *str, int *i);
int			parse_output(char *str, int i, t_cmd *c);
void		print_struct(t_cmd c);
void		init(t_cmd *c, char *str, t_korn *korn);
t_cmd		command_init(char *str, t_korn *korn);
t_cmd		*t_cmd_init(char **splitted, t_korn **korn);
void		parse(char *str, t_korn **korn);
int			parse_input(char *str, int i, t_cmd *c, t_korn *korn);
void		heredoc(void);
void		fill(char **to, char *from);
char		**first_step(char *str);
int			line_count(char **splitted);
char		**output_redirs(char *s, int *count);
char		**input_redirs(char *s, int *count, t_korn *korn);
int			get_output_flag(char *str);



#endif

// ◦ echo 	✅✅✅
// ◦ cd		✅✅✅
// ◦ pwd 	✅✅✅
// ◦ export ✅✅✅
// ◦ unset 	✅✅✅
// ◦ env  	✅✅✅
// ◦ exit 	✅✅✅