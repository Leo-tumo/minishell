#include "../includes/minishell.h"

int main(void)
{
    while (1)
    {
        char * str = readline(BEGIN(49, 31)BOLD"minihell $> "CLOSE);
        free(str);
    }
}