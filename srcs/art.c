/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   art.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 14:49:28 by letumany          #+#    #+#             */
/*   Updated: 2022/04/15 14:50:02 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("               -,-..\\  _  \\  `  /  %s,%s  / `._) _,-\\`       \\ \n",
		RED, GREEN);
	printf("                \\_,,.) %s/\\    %s` /  %s/ )%s",
		RED, GREEN, RED, GREEN);
	printf(" (-,, ``    ,        |\n");
	printf("               ,` )  | %s\\_\\       '-`%s  |  `(               \\ \n",
		RED, GREEN);
	printf("              /  /```(   , --, ,' \\   |`<`    ,            |\n");
	printf("             /  /_,--`\\   <\\  V /> ,` )<_/)  | \\      _____)\n");
}

void	print_monster2(void)
{
	print_monster();
	printf("       ,-, ,`   `   (_,\\ \\    |   /) / __/  /   `----`\n");
	printf("      (-, \\           ) \\ ('_.-._)/ /,`    /\n");
	printf("      | /  `          `/ \\ V    V, /`     /\n");
	printf("   ,--\\(        ,     <_/`\\      ||      /\n");
	printf("  (   ,``-     \\/|         \\-A.A-`|     /\n");
	printf(" ,>,_ )_,..(    )\\          -,,_-`  _--`\n");
	printf("(_ \\|`   _,/_  /  \\_            ,--`\n");
	printf(" \\( `   <.,../`     `-.._   _,-`\n");
	printf("888     888'Y88   e88 88e            e Y8b    Y8b Y88888P   e88 ");
	printf("88e   \n888     888 ,'Y  d888 888b          d8b Y8b    Y8b Y888P");
	printf("   d888 888b  \n888     888C8   C8888 8888D  888   d888b Y8b    Y");
	printf("8b Y8P   C8888 8888D \n888  ,d 888 \",d  Y888 888P        d8888888");
	printf("88b    Y8b Y     Y888 888P  \n888,d88 888,d88   \"88 88\"        d");
	printf("8888888b Y8b    Y8P       \"88 88\"   \n                           \n");
}

void	print_welcome_message(void)
{
	print_monster2();
	printf("    e   e     888 Y88b Y88 888  dP\"8 888 888 888'Y88 888     888\n");
	printf("   d8b d8b    888  Y88b Y8 888 C8b Y 888 888 888 ,'Y 888     888\n");
	printf("  e Y8b Y8b   888 b Y88b Y 888  Y8b  8888888 888C8   888     888\n");
	printf(" d8b Y8b Y8b  888 8b Y88b  888 b Y8D 888 888 888 \",d 888  ,d 88");
	printf("8  ,d \nd888b Y8b Y8b 888 88b Y88b 888 8edP  888 888 888,d88 888,");
	printf("d88 888,d88 %s\n", WHITE);
}

/* 
** Shows the prompt via readline
*/
char	*show_prompt(t_korn *korn)
{
	char	*line;

	while (1)
	{
		run_signals(1);
		line = readline(get_value("PS1", korn->env_head));
		if (!line)
		{
			run_signals(1);
			ft_putstr_fd("\033[1A", 2);
			ft_putstr_fd("\033[23C", 2);
			ft_putendl_fd("exit", 2);
			exit(0);
		}
		else if (*line == '\0')
			free(line);
		else
		{
			if (ft_strlen(line) == 0)
				continue ;
			add_history(line);
		}
		parse(line, &korn);
	}
	return (line);
}
