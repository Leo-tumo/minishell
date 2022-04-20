#include "../includes/minishell.h"

void	print_struct(t_cmd c)
{
	int	j;
	j = -1;
	printf("=============INFILES=============\n");
	while (++j < c.infile_count)
		printf("INFILE #%d === %s\n", j + 1, c.infile[j]);
	j = -1;
	printf("=============OUTFILES============\n");
	while (++j < c.outfile_count)
		printf("OUTFILE #%d === %s, FLAG === %x\n", j + 1, c.outfile[j], c.output_flag);
	j = -1;
	printf("=============HEREFUCK============\n");
	while (++j < c.doc->heredoc_count)
		printf("DELIM #%d === %s, D_Q === %d\n", j + 1, c.doc->delimiters[j], c.doc->d_q);
	printf("COMMMMMAND ======= %s\n", c.argv[0]);
	printf("============ ARGUMENTS===========\n");
	j = 0;
	while (++j < c.arg_index)
		printf("ARGV[%d] === %s\n", j, c.argv[j]);
}

void	fill(char **to, char *from)
{
	int		len_from;
	int		len_to;
	char	*tmp;
	int		i;

	i = -1;
	tmp = *to;
	len_to = ft_strlen(*to);
	len_from = ft_strlen(from);
	while (++i < len_from)
	{
		*tmp = *from;
		++tmp;
		++from;
	}
	while (++i < len_to)
	{
		*tmp = '\0';
		++tmp;
	}
}

char	**first_step(char *str)
{
	char	**ret;
	char	*tmp1;
	int		i;

	i = -1;
	ret = ft_split(str, '|');
	while (ret[++i] != NULL)
	{
		tmp1 = ft_strtrim(ret[i], " ");
		free(ret[i]);
		ret[i] = tmp1;
		// free(tmp1);
	}
	return (ret);
}

int	line_count(char **splitted)
{
	int	i;	
	int	lines;

	i = -1;
	lines = 0;
	while (splitted[++i] != NULL)
		++lines;
	return (lines);
}
