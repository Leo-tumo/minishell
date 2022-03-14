#include "../includes/minishell.h"

/*  
** Check id Var name is valid
** it can only be _ or letters 
** ex. _VAr="some sh*t", _VAr+=77777
*/
int    is_valid_name(char  *str)
{
    if (!ft_isalpha(*str) && *str != '_')
        return (False);
    str++;
    while (*str && *str != '=')
    {
        if (!ft_isalnum(*str) && *str != '_')
            if (!(*str == '+' && *(str +1) && *(str + 1) == '='))
                return (False);
        str++;
    }
    return (True);
}

/*  
** export without arguments , just printing list
*/
int    export(int fd, t_env *env)
{
    t_env   *tmp;

    tmp = env;
    while (tmp->next)
    {
        ft_putstr_fd("declare -x ", fd);
        ft_putstr_fd(tmp->name, fd);
        if (tmp->data)
        {
            write(fd, "=\"", 2);
            ft_putstr_fd(tmp->data, fd);
            write(fd, "\"\n", 2);
        }
        tmp = tmp->next;
    }
    return (0);
}

/*  
** export with arguments
*/
int    export_(char**s, t_env *head)
{
    int     i;
    int     sign;
    int     empty_value;
    int     ret;

    i = 0;
    ret = 0;
    while (s[i])
    {
        if (!(is_valid_name(s[i])))
        {
            printf(" bash: export: `%s': not a valid identifier", s[i]);
            ret = 1;
            ++i;
        }
        sign = export_append(s[i]);
        empty_value = check_value(s[i]);
        if (check_existance(s[i], head))
            renew_var(char *s, int sign, empty_value);
        else
            append_var(char *s, int sign, empty_value);

    }
    return (ret);
}


// TODO check if name is right DONE:
// TODO if_wrong =>  bash: export: `NAME': not a valid identifier \n
// TODO: check if there's an unexported variable with that name
// TODO: check if it's '=' or '+='
// TODO: check if it's already in the list
// TODO: if in_list { if2 '+=' => append else2 replace } 
// TODO: else create new - 
// TODO: if argument is empty - {if2 = '+' => leave it empty, else2 = '+='add 'space'}
