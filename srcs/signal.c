#include "../includes/minishell.h"
int		g_ret_number = 0;

void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\033[K");
		printf("^C\n");
	}

	if (rl_on_new_line() == -1) // readline Output the string set to ?
		exit(1);
	rl_replace_line("", 1); // Throws out the string already typed in the prompt.
	rl_redisplay();         // Prevents prompt cursor from moving.
}

void setting_signal()
{
	signal(SIGINT, sig_handler); // CTRL + C
	signal(SIGQUIT, SIG_IGN);    // CTRL + /
	// signal(SIGTERM, sig_handler);     /7  // signal(SIGTERM, sig_handler);
}

// int main()
// {
// 	char *str;
// 	struct termios term;
// 	tcgetattr(STDIN_FILENO, &term);
// 	term.c_lflag &= ~(ECHOCTL);
// 	tcsetattr(STDIN_FILENO, TCSANOW, &term);
// 	setting_signal();

// 	while (1)
// 	{
// 		str = readline(GREEN"nanoshell$ ");
// 		if (!str)
// 		{
// 			printf("\033[1A");
// 			printf("\033[10C");
// 			printf(" exit\n");
// 			exit(-1);
// 		}
// 		else if (*str == '\0')
// 		{
// 			free(str);
// 		}
// 		else
// 		{
// 			add_history(str);
// 			printf("%s\n", str);
// 			free(str);
// 		}
// 	}

// 	return (0);
// }




void	restore_prompt(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	g_ret_number = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	g_ret_number = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}
void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}