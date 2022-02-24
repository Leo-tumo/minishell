#include "../includes/minishell.h"
# define CLOSE "\033[0m"                 // Закрыть все свойства
# define BLOD  "\033[1m"                 // BOLD
# define BEGIN(x,y) "\033["#x";"#y"m"    // x: background, y: foreground

int main(void)
{
    while (1)
    {
        char * str = readline(BEGIN(49, 31)"minihell $> "CLOSE);
        free(str);
    }
}