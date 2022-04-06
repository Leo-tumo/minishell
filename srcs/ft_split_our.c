#include "../includes/minishell.h"

static int	word_count(char const *s, char c)
{
	int		i;
	int		count;
	char	quote;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] == '\'' || s[i] == '"') && s[++i])
		{
			quote = s[i - 1];
			while (s[i] != quote)
				++i;
		}
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			++count;
		++i;
	}
	return (count);
}

static int	word_length(char const *s, char c)
{
	int		i;
	int		len;
	char	quote;

	i = -1;
	len = 0;
	while (s[++i] != c && s[i] != '\0')
	{
		if ((s[i] == '\'' || s[i] == '"') && s[++i])
		{
			quote = s[i - 1];
			++len;
			while (s[i] != quote)
			{
				++len;
				++i;
			}
		}
		len++;
	}
	return (len);
}

static char	**f(char const *s, char c, char **result, int words_count)
{
	int	i;
	int	j;
	int	w_len;

	while (*s == c)
		s++;
	i = -1;
	while (++i < words_count)
	{
		while (*s == c)
			s++;
		j = -1;
		w_len = word_length(s, c);
		result[i] = (char *)malloc(sizeof(char) * (w_len + 1));
		if (!result[i])
			return (NULL);
		while (++j < w_len)
		{
			result[i][j] = *s;
			s++;
		}
		result[i][j] = '\0';
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wcount;

	if (!s)
		return (NULL);
	wcount = word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (wcount + 1));
	if (!result)
		return (NULL);
	result = f(s, c, result, wcount);
	return (result);
}
