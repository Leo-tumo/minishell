#include "../includes/minishell.h"

/*  
** Separates var name from value
*/
char	**env_split(char *str)
{
	int		i;
	char	**s;

	i = 0;
	s = ft_calloc(2, sizeof(char *));
	while (str[i] != '=')
		++i;
	s[0] = ft_substr(str, 0, i);
	str += i + 1;
	s[1] = ft_strdup(str);
	return (s);
}

/* 
** keep environment variables in a linked list
*/
t_env	*env_keeper(char **env)
{
	char	**s;
	t_env	*head;
	t_env	*current;
	t_env	*temp;

	current = NULL;
	temp = NULL;
	head = NULL;
	while (*env != NULL)
	{
		temp = (t_env *)malloc(sizeof(t_env));
		s = env_split(*env);
		temp->name = s[0];
		temp->data = s[1];
		temp->next = NULL;
		temp->blind = 1;
		free (s);
		if (!head)
			head = temp;
		else
			current->next = temp;
		current = temp;
		env++;
	}
	return (head);
}
