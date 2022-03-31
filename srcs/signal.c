#include "../includes/minishell.h"
int		g_ret_number = 0;

void sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\033[K");
		// printf("%sAvôeL> %s\n", MAGENTA, WHITE);
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
}

int main()
{
	char *str;
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	setting_signal();
	pid_t	child_pid = fork();
	if (child_pid == 0)
	{
		while (1)
		{
			signal(SIGINT, SIG_DFL);
			str = readline(MAGENTA"AvôeL> "WHITE);
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
				signal(SIGINT, SIG_DFL);
				execl("/bin/cat", "cat", NULL);
				free(str);
			}
		}
	}
	else{
		int stat_loc;
		setting_signal();
		waitpid(child_pid, &stat_loc, WUNTRACED);
		perror("Error\n");
		printf("Exit status = %d\n",  WEXITSTATUS(stat_loc));
		while(1)
		{
			term.c_lflag &= ~(ECHOCTL);
			str = readline("PAPA");
			if (!str)
			{
				printf("\033[1A");
				printf("\033[10C");
				printf(" exit\n");
				exit(-1);
			}
		}	
	}

	return (0);
}


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
	printf("Quit :3\n");
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
