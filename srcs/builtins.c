#include "../includes/minishell.h"

/*  
**  echo "$unknown_var" => '\n'
**  echo -n "$unknown_var" => 
**  echo xcho => xcho
**  echo $HOME =>  /Users/letumany
**  echo '$HOME' => $HOME
*/
int	echo(char **str, int fd, int flag, int argc)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 0;
	while (i < argc)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			ret += write(fd, &str[i][j], 1);
			++j;
		}
		if (i != argc - 1)
			ret += write(fd, " ", 1);
		++i;
	}
	if (flag == FALSE)
		write (fd, "\n", 1);
	return (ret);
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
