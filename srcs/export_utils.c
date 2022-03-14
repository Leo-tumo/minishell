#include "../includes/minishell.h"

/*  
** Checks if var should append or replace - '=' vs '+='
*/
int     export_append(char *s)
{
    int     i;

    i = 0;
    while (ft_isalnum(s[i]) || s[i] == '_')
        ++i;
    if (s[i] == '+')
        return (True);
    else
        return (False);
}


/*  
** Checks if variable has value or is empty
*/
int     check_value(char *s)
{
    int     i;

    i = 0;
    while (s[i] && s[i] != '=')
        ++i;
    if (!s[i] || s[i] == ' ')
        return (False);
    else
        return (True);
}


/*  
** Check if the variable that will be exported
** is new or already exists
*/
int     check_existance(char *s, t_env *head)
{
    t_env   *tmp;
    int     len;

    tmp = head;
    while (tmp->next)
    {
        if (ft_strlen(s) >= ft_strlen(tmp->name))
        {
            if (ft_strncmp(s, tmp->name, ft_strlen(tmp->name)) == 0)
                return (True);
        }
        tmp = tmp->next;   
    }
    return (False);
}

void    renew_var(char *new_var, int append, int has_value, t_env *head)
{
    t_env   *tmp;
    int     i;
    char    **var;
    char    *name;

    
    var = NULL;
    var = env_split(new_var);
    tmp = head;
    i = 0;
    if (!append)
    {
        while (ft_strncmp(var[0], tmp->name, ft_strlen(var[0]) + 1) != 0)
            tmp = tmp->next;
        if (tmp->data!= NULL)
            ft_bzero(tmp->data, ft_strlen(tmp->data));
        if (has_value)
            ft_strlcpy(tmp_data, var[1])
    }
    else
    {

    }

}

char    *remove_plus_sign(char *s)
{
    int     i;
    char    *new_name;

    i = 0;
    new_name = (char *)malloc(ft_strlen(s) + 1);
    while(s[i])
    {
        new_name[i] = s[i];
        if (s[i] == '+')
        {
            new_name[i] = '\0';
            break;
        }
        ++i;
    }
    return (new_name);
}