#include "../includes/minishell.h"

/* 
** Shows the content of chosen directory
*/
int	mini_ls(char *path)
{
	struct dirent	*de;
	DIR				*dr;

	dr = opendir(path);
	if (dr == NULL)
	{
		perror("Could not open current directory");
		return (0);
	}
	de = readdir(dr);
	while (de != NULL)
	{
		printf("%s\n", de->d_name);
		de = readdir(dr);
	}
	closedir (dr);
	return (0);
}

/*  
** prints current working directory to given fd
** works even if PWD is unset
*/
int	pwd(t_korn *korn)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putstr_fd(pwd, korn->out);
	ft_putstr_fd("\n", korn->out);
	return (0);
}
