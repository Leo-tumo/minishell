#include "../includes/minishell.h"

void	input_opener(t_cmd *cmd)
{
	int		i;
	int		fd;

	i = 0;
	while (i < cmd->infile_count)
	{
		fd = open(cmd->infile[i], O_RDONLY);
		if (fd == -1)
		{
			perror(ft_strjoin("bash: ", cmd->infile[i]));
			cmd->input = -1;
			return;
		}
		if (++i < cmd->infile_count)
			close(fd);
	}
}

void	output_opener(t_cmd *cmd)
{
	int		i;
	int		fd;

	i = 0;
	while (i < cmd->outfile_count)
	{
		fd = open(cmd->outfile[i], O_RDONLY | O_CREAT | cmd->output_flag);
		if (fd == -1)
		{
			perror(ft_strjoin("bash: ", cmd->outfile[i]));
			cmd->output = -1;
			return;
		}
		if (++i < cmd->outfile_count)
			close(fd);
	}
}
