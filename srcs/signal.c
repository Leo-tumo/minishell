#include "../includes/minishell.h"

/*  
** ^C signal inside heredoc
*/
void	doc_ctrl_c(int sig)
{
	g_sig.exit_status = sig + SIG_PLUS;
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
	g_sig.exit_status = sig + SIG_PLUS;
	write(1, "\n", 1);
	(void)sig;
}

/*
** For ^\ signal inside child process
*/
void	back_slash(int sig)
{
	g_sig.exit_status = sig + SIG_PLUS;
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
	term.c_lflag &= ~ECHO;
	term.c_lflag &= ~(ECHOCTL);
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		g_sig.exit_status = 0;
	}
	else if (sig == 3)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
	else if (sig == 4)
		sig_heredoc();
}
