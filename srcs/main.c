#include "../includes/minishell.h"



void	print_monster(void)
{
	printf("%s                                             ,--,  ,.-.\n", GREEN);
	printf("               ,                   \\,       '-,-`,'-.' | ._\n");
	printf("              /|           \\    ,   |\\         }  )/  / `-,',\n");
	printf("              [ ,          |\\  /|   | |        /  \\|  |/`  ,`\n");
	printf("              | |       ,.`  `,` `, | |  _,...(   (      .',\n");
	printf("              \\  \\  __ ,-` `  ,  , `/ |,'      Y     (   /_L\\ \n");
	printf("               \\  \\_\\,``,   ` , ,  /  |         )         _,/\n");
	printf("                \\  '  `  ,_ _`_,-,<._.<        /         /\n");
	printf("                 ', `>.,`  `  `   ,., |_      |         /\n");
	printf("                   \\/`  `,   `   ,`  | /__,.-`    _,   `\\ \n");
	printf("               -,-..\\  _  \\  `  /  %s,%s  / `._) _,-\\`       \\ \n", RED, GREEN);
	printf("                \\_,,.) %s/\\    %s` /  %s/ )%s (-,, ``    ,        |\n",RED, GREEN, RED, GREEN);
	printf("               ,` )  | %s\\_\\       '-`%s  |  `(               \\ \n", RED, GREEN);
	printf("              /  /```(   , --, ,' \\   |`<`    ,            |\n");
	printf("             /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)\n");
	printf("       ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`\n");
	printf("      (-, \\           ) \\ ('_.-._)/ /,`    /\n");
	printf("      | /  `          `/ \\ V   V, /`     /\n");
	printf("   ,--\\(        ,     <_/`\\     ||      /\n");
	printf("  (   ,``-     \\/|         \\-A.A-`|     /\n");
	printf(" ,>,_ )_,..(    )\\          -,,_-`  _--`\n");
	printf("(_ \\|`   _,/_  /  \\_            ,--`\n");
	printf(" \\( `   <.,../`     `-.._   _,-`\n");
}

void	print_welcome_message(void)
{
	print_monster();
	printf("888     888'Y88   e88 88e            e Y8b    Y8b Y88888P   e88 88e   \n");
	printf("888     888 ,'Y  d888 888b          d8b Y8b    Y8b Y888P   d888 888b  \n");
	printf("888     888C8   C8888 8888D  888   d888b Y8b    Y8b Y8P   C8888 8888D \n");
	printf("888  ,d 888 \",d  Y888 888P        d888888888b    Y8b Y     Y888 888P  \n");
	printf("888,d88 888,d88   \"88 88\"        d8888888b Y8b    Y8P       \"88 88\"   \n");
	printf("                                                                       \n");
	printf("                                                                       \n");

	printf("    e   e     888 Y88b Y88 888  dP\"8 888 888 888'Y88 888     888     \n");
	printf("   d8b d8b    888  Y88b Y8 888 C8b Y 888 888 888 ,'Y 888     888     \n");
	printf("  e Y8b Y8b   888 b Y88b Y 888  Y8b  8888888 888C8   888     888     \n");
	printf(" d8b Y8b Y8b  888 8b Y88b  888 b Y8D 888 888 888 \",d 888  ,d 888  ,d \n");
	printf("d888b Y8b Y8b 888 88b Y88b 888 8edP  888 888 888,d88 888,d88 888,d88 %s\n", WHITE);
}

int	main(int argc, char **argv, char **env)
{
	t_korn		*korn;
	// t_env		*track;

	print_welcome_message();
	(void)argc;
	(void)argv;
	data_init(&korn);
	korn->env_head = env_keeper(env);
	// track = korn->env_head;

	t_cmd	*cmd = malloc(sizeof(t_cmd));
	cmd->args = "Hello my friend";
	cmd->output = 1;
	// ft_echo(cmd);  FIXME: seg fault 

	show_prompt();
	return (0);
}

/* 
** Shows the prompt via readline
*/
char	*show_prompt(void)
{
	char	*line;

	while (1)
	{
		line = readline("AvôeL> "WHITE);
		if (!line)
			break ;
		if (ft_strlen(line) == 0)
			continue ;
		add_history(line);
		free(line);
	}
	return (line);
}

/* 
** initialize main data structure 
*/
void	data_init(t_korn **korn)
{
	*korn = (t_korn *)malloc(sizeof(t_korn));
	(*korn)->env_head = NULL;
}

