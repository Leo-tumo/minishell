#include "../includes/minishell.h"

/*  
** ^C signal inside heredoc
*/
void	doc_ctrl_c(int sig)
{
	g_sig.exit_status = 131;
	printf("\033[1A");
	printf("\033[0C");
	exit(131);
	(void)sig;
}

/*  
** ^C signal in child process
*/
void	ctrl_c(int sig)
{
	g_sig.exit_status = 130;
	write(1, "\n", 1);
	(void)sig;
}

/*
** For ^\ signal inside child process
*/
void	back_slash(int sig)
{
	g_sig.exit_status = 131;
	printf("Quit :3\n");
	(void)sig;
}

/*  
** Signal handler for heredoc
** ^D displays Error message
** ^\ is ignored
** ^C works normal, exit status 131
*/
void	sig_heredoc(void)
{
	g_sig.exit_status = 131;
	signal(SIGINT, doc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

/*  
** 1 -> for parent
** 2 -> for child
** 3 -> for ^D aka EOF
*/
void	run_signals(int sig)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
		g_sig.exit_status = 0;
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	if (sig == 3)
	{
		printf("\033[1A");
		printf("\033[10C");
		printf("exit\n");
		exit(0);
	}
	if (sig == 4)
		sig_heredoc();
}

// FIXME: 👇🏻 Don't wanna delete this for now
// void sig_handler(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("\033[K");
// 		// printf("%sAvôeL> %s\n", MAGENTA, WHITE);
// 	}
// 	if (rl_on_new_line() == -1) // readline Output the string set to ?
// 		exit(1);
// 	rl_replace_line("", 1); // Throws out the string already typed in the prompt.
// 	rl_redisplay();         // Prevents prompt cursor from moving.
// }

// void setting_signal()
// {
// 	signal(SIGINT, sig_handler); // CTRL + C
// 	signal(SIGQUIT, SIG_IGN);    // CTRL + /
// }
