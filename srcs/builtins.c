#include "../includes/minishell.h"

/*  
**  echo "$unknown_var" => '\n'
**  echo -n "$unknown_var" => 
**  echo xcho => xcho
**  echo $HOME =>  /Users/letumany
**  echo '$HOME' => $HOME
*/
int    echo(char **str, int fd, int flag, int argc)
{
    int     i;
    int     j;
    int     ret = 0;

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
    if (flag == False)
        write (fd, "\n", 1);
    return ret;
}

/* 
** Shows the content of chosen directory
*/
int mini_ls(char *path)
{
    struct dirent   *de;
    DIR             *dr;

    dr = opendir(path);
    if (dr == NULL) 
    {
        perror("Could not open current directory");
        return 0;
    }
  
    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);
  
    closedir(dr);    
    return 0;
}
