#include "../includes/minishell.h"

/*  
** I hate libft's strncmp -> that 'n' is disgusting
*/
int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i])
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	if (s2[i] == '\0')
		return (0);
	else
		return (-s2[i]);
}

/*  
** 		 if string gcontains any '$' sign
**		returns -TRUE- else returns -FALSE-
*/
int	check_dollar_sign(char	*str)
{
	while (*str)
	{
		if (*str == '$')
			return (TRUE);
		str++;
	}
	return (FALSE);
}

/*  
** 		replaces $ var with it's value
*/
char	*replace_dollar(char * ret, char **var_name, char **str, t_env *env)
{
	char_join(**str, var_name);
	(*str)++;
	while(ft_isalnum(**str) || **str == '_')
		*str += char_join(**str, var_name);
	if (ret)
		ret = ft_strjoin(ret, get_value(*var_name, env));
	else
		ret = get_value(*var_name, env);
	return (ret);
}

char	*replace_var(char *str, t_env *env)
{
	char	*ret;
	char	*var_name;

	ret = NULL;
	while (*str)
	{
		if (*str == '$')
		{
			var_name = NULL;
			str++;
			if (ft_ispace(*str) || !*str)
				char_join('$', &ret);
			else if (*str == '?')			
				str += char_join('0', &ret);
			else if (*str == '_' || ft_isalpha(*str))
				ret = replace_dollar(ret, &var_name, &str, env);
			else
				++str;
		}
		else
			str += char_join(*str, &ret);
	}
	return (ret);
}

/*  
** Actual heredoc is here, inside child process
*/
void	heredoc_child(t_korn *korn, int fd, char *delimiter)
{
	char	*buf;

	buf = readline("> ");
	while (buf)
	{
		korn->line++;
		if (check_dollar_sign(buf))
			buf = replace_var(buf, korn->env_head);
		ft_putendl_fd(buf, fd);
		free(buf);
		buf = readline("> ");
		if (!ft_strcmp(buf, delimiter))
		{
			free(buf);
			exit(0);
		}
		if (!buf)
		{
			printf("bash: warning: here-document at line %d delimited ", korn->line);
			printf("by end-of-file (wanted `%s')\n", delimiter);
			exit(0);
		}
	}
}

/*  
** This is fake heredoc, in case of multiple heredocs 2🍕
*/
void	fake_heredoc(t_korn *korn, char *delimiter)
{
	char	*buf;

	korn->heredoc_count--;
	buf = readline("> ");
	while (ft_strcmp(buf, delimiter))
	{
		free(buf);
		buf = readline("> ");
		korn->line++;
		if (!buf)
		{
			printf("bash: warning: here-document at line %d delimited ", korn->line);
			printf("by end-of-file (wanted `%s')\n", delimiter);
			return;
		}
	}
}

/*  
** This function allows us to get heredoc's output to STDIN
** if there are multiple heredocs, it fake them except the last one
*/
void	here_doc(t_korn *korn)
{
	int		fd[2];
	pid_t	pid;
	int		i;

	i = 0;
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		run_signals(4);
		while (i + 1 < korn->heredoc_count)
		{
			fake_heredoc(korn, korn->delimiters[i]);
			++i;
		}
		heredoc_child(korn, fd[1], korn->delimiters[i]);
		close(fd[0]);
	}
	else
	{
		run_signals(1);
		waitpid(pid, &g_sig.exit_status, WEXITSTATUS(g_sig.exit_status));
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
}

// extern char **environ;
// int	main() // TODO: Just for test - I think it works!needless to say that I'm not sure about it.
// {
// 	t_korn	*korn = malloc(sizeof(t_korn));

// 	t_env	*env = malloc(sizeof(t_env));
// 	env = env_keeper(environ);
// 	korn->env_head = env;

// 	korn->line = 0;
// 	korn->heredoc_count = 1;
// 	korn->delimiters = malloc(sizeof(char**));
// 	korn->delimiters[0] = malloc(sizeof(char *));
// 	korn->delimiters[0] = "eof";
// 	here_doc(korn);
// 	execl("/bin/cat", "cat", NULL);
// } 