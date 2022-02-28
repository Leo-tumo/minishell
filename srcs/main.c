#include "../includes/minishell.h"

int main(void)
{
    while (1)
    {
        char * str = readline("minihell $> ");
		rl_replace_line("How", 1);
	
        add_history(str);
        if (str[0] == '-')
            clear_history();
        free(str);
    }
}
