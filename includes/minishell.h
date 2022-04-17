/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <letumany@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:48:49 by letumany          #+#    #+#             */
/*   Updated: 2022/04/17 20:14:34 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <fcntl.h>

# define WHITE "\001\033[0m\002"
# define RED "\001\033[1;31m\002"
# define CYAN "\001\033[1;36m\002"
# define GREEN "\001\033[1;92m\002"
# define MAGENTA "\001\033[1;35m\002"

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
# define SIG_PLUS			128 // if signaled exit status = 128 + sig

/*  
** Struct for command
*/
typedef struct s_cmd
{
	char		*name; // command name - ex. echo, cd, yes, tee, cal etc...
	char		*path; // this is very important -> commands full path
	char		**argv; // needed for execve || can be replaced by ft_split(args, " "). Should include command's name
	int			argc; // argument count
	int			input;
	int			output;
	int			id; // 0 = other, 1 = echo, 2 = cd, 3 = pwd, 4 = export, 5 = unset, 6 = env, 7 = exit
	int			stat; // exit status for each command;
	char		**infile;
	int			infile_count;//? malloci hamar
	int			input_index;
	char		**outfile;
	int			outfile_count; //?malloci hamar
	int			output_flag; //O_TRUNC kam O_APPEND kaxvac outputi tipic
	int			output_index; //for the malloc in 2d output array
	int			arg_index;
	char		*quote_flags;
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
*/
typedef struct s_korn
{
	int		line; // counts lines for heredoc error message
	int		d_q; // if final delimiter is quoted = 1 else 0
	int		heredoc_count; // in case that there are many Speciall for 2🍕s
	char	**delimiters; // heredoc delimiters' gang ✵ - should replace t_doc linked list;
	int		receiver; // fd of receiver
	t_env	*env_head;	// head of env variables
	int		cmd_count; // count of commands
	t_cmd	*cmd; // commands themself
	pid_t	*child; // pid array for processes
}			t_korn;

/* 
** 		---	Starters ---
*/
void		shlvl_(t_env **env);
void		run_signals(int sig); 
t_env		*env_keeper(char **env);
void		restore_prompt(int sig);
void		data_init(t_korn **korn);
char		*show_prompt(t_korn *korn);
void		print_welcome_message(void);
void		here_doc(t_korn *korn);

/*  
** Execution functions
*/
void		ctrl_c(int sig);
void		back_slash(int sig);
void		pi_open(t_korn *korn);
void		close_one(t_cmd *cmd);
int			is_builtin(t_cmd cmd);
void		fd_closer(t_korn korn);
void		incubator(t_korn *korn);
char		**ll_to_matrix(t_env *env);
t_cmd		*find_child(t_korn *korn, pid_t pid);
void		close_them(t_korn *korn, int index);

/*  
** util functions
*/
void		free2(char **s);
void		close_2(int *fd);
char		*lower_(char const *s);
char		**env_split(char *str);
int			guns_n_roses(char *name);
int			char_join(char c, char **s1);
void		free_root(t_korn *korn, int kill);
int			pathfinder(t_cmd *cmd, t_korn *korn);
void		delete_var(t_env **head, char *key);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin3(const char *s1, const char *s2, const char *s3);
char		*repl_dollar(char *ret, char **var_name, char **str, t_env *env);

/*  
** builtins and their utils
*/
int			echo_(t_cmd *cmd);
int			check_value(char *s);
int			export_append(char *s);
int			is_valid_name(char *str);
char		*remove_plus_sign(char *s);
int			pwd_(t_cmd cmd, t_env *env);
int			export_p(int fd, t_env *env);
int			cd_(char *path, t_env *head);
int			env_(t_korn *korn, t_cmd *cmd);
int			export_v(char**s, t_env *head);
int			exit_(t_cmd *cmd, t_korn *korn);
int			unset_(t_korn *korn, t_cmd *cmd);
char		*get_value(char *name, t_env *head);
int			check_existance(char *s, t_env *head);
void		append_var(char *str, int flags, t_env *head);
void		renew_var(char *new_var, int append, int has_value, t_env *head);

/* 
** 		file status checking functions 
*/
int			is_file(char *path);
void		fd_closer(t_korn korn);
int			is_directory(char *path);
int			is_executable(char *path);

/*
** 		Parsing functions ⇣⇣
*/
void		heredoc(void);
int			ft_ispace(int c);
void		print_struct(t_cmd c);
char		**first_step(char *str);
char		**first_step(char *str);
int			get_output_flag(char *str);
int			line_count(char **splitted);
void		fill(char **to, char *from);
void		parse(char *str, t_korn **korn);
char		*get_filename(char *str, int *i);
char		*double_output(char *str, int *i);
char		**output_redirs(char *s, int *count);
t_cmd		command_init(char *str, t_korn *korn);
char		*get_quoted_filename(char *str, int *i);
void		init(t_cmd *c, char *str, t_korn *korn);
int			parse_output(char *str, int i, t_cmd *c);
t_cmd		*t_cmd_init(char **splitted, t_korn **korn);
char		**input_redirs(char *s, int *count, t_korn *korn);
int			parse_input(char *str, int i, t_cmd *c);



#endif

// ◦ echo 	✅✅✅
// ◦ cd		✅✅✅
// ◦ pwd 	✅✅✅
// ◦ export ✅✅✅
// ◦ unset 	✅✅✅
// ◦ env  	✅✅✅
// ◦ exit 	✅✅✅