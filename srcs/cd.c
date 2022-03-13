#include "../includes/minishell.h"

void    cd()
{
    printf("%s\n", getenv("PWD"));
}