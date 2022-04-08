#include "../includes/minishell.h"

/*  
** prints current working directory to given fd
** works even if PWD is unset
*/
int	pwd_(t_cmd cmd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_putendl_fd(pwd, cmd.output);
	ft_putstr_fd("\n", cmd.output);
	g_sig.exit_status = 0;
	return (0);
}

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
