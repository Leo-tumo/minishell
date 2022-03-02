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

typedef struct s_cmd
{
	char	*infile;
	int		double_input;
	char	*outfile;
	int		double_output;
	char	*flag;
	char	*argument;
	char	*name;

}	t_cmd;

void	fill(char **to, char *from);
char	**first_step(char *str);

#endif