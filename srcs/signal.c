#include "../includes/minishell.h"

void sig_handler(int signal)
{
    if (signal == SIGINT)
    {
        printf("\033[K");
        printf("♠️♠️🫥> \n");
    }

    if (rl_on_new_line() == -1) // readline Output the string set to ?
        exit(1);
    rl_replace_line("" 1); // Throws out the string already typed in the prompt.
    rl_redisplay();         // Prevents prompt cursor from moving.
}

void setting_signal()
{
    signal(SIGINT, sig_handler); // CTRL + C
    signal(SIGQUIT, SIG_IGN);    // CTRL + /
    // signal(SIGTERM, sig_handler);       // signal(SIGTERM, sig_handler);
}

int main()
{
    char *str;
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    setting_signal();

    while (1)
    {
        str = readline("nanoshell$ ");
        if (!str)
        {
            printf("\033[1A");
            printf("\033[10C");
            printf(" exit\n");
            exit(-1);
        }
        else if (*str == '\0')
        {
            free(str);
        }
        else
        {
            add_history(str);
            printf("%s\n", str);
            free(str);
        }
    }

    return (0);
}