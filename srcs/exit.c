#include "../includes/minishell.h"

/*  
** Frees cmd members and cmd, after execution
*/
void    free_cmd(t_cmd *cmd)
{
    free(cmd->name);
    free(cmd->path);
    free(cmd->args);
    free(cmd->argv);
    free(cmd);
}

/*  
** Not ready yet. too long. exits only parrent.
** can take only 1 int argument. if arg > 256 returns arg % 256
** have to test this, i think it should always exit
** if argument ain't numeric - exits and returns 0
** if it has many arguments - just returns error message and 1
** else returns arg % 256 as mentioned
*/
int  ft_exit(t_korn *korn, t_cmd *cmd)   // FIXME:
{
    int i;
    char    **argv;

    argv = ft_split(cmd->args, ' ');
    if (korn->argc > 2)
    {
        ft_putstr_fd("exit\n bash: exit: too many arguments\n", 2);
        g_sig.exit_status = 1;
    }
    else
    {
        i = 0;
        while (cmd->argc > 1 && ft_isdigit(cmd->argv[1][i])) 
            i++;
        if (cmd->argc > 1 && cmd->argv[1][i])
        {
            ft_putstr_fd("exit\nbash: exit: ", 2);
            ft_putstr_fd(cmd->argv[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            g_sig.exit_status = 2;
        }
        if (cmd->argc > 1 && g_sig.exit_status != 2)
           i = ft_atoi(cmd->argv[1]) % 256; 
        else
            i = g_sig.exit_status;
        free_cmd(cmd);  
        exit(i); 
    }
    return (g_sig.exit_status);
}
