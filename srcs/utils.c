#include "../includes/minishell.h"

/*  
** Allocates (with malloc) and returns a new
** string, which is the result of the concatenation
** of 's1' + 's2' + 's3'.
*/
char	*ft_strjoin3(const char *s1, const char *s2, const char *s3)
{
	char	*tmp;

	tmp = NULL;
	if (s1 && s2 && s3)
	{
		if ((tmp = ft_strjoin(s1, s2)))
			tmp = ft_strjoin(tmp, s3);
	}
	return (tmp);
}