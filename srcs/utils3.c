#include "../includes/minishell.h"

/*
** Transforms linked list to char**
*/
char	**ll_to_matrix(t_env *env)
{
	t_env	*tmp;
	int		i;
	char	**array;

	i = 0;
	tmp = env;
	array = malloc(sizeof(char **));
	while (tmp != NULL)
	{
		if (tmp->data)
			array[i] = ft_strjoin3(tmp->name, "=", tmp->data);
		else
			array[i] = ft_strdup(tmp->name);
		i++;
		tmp = tmp->next;
	}
	return (array);
}
