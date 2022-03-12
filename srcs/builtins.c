#include "../includes/minishell.h"

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
