/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: letumany <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 02:14:34 by letumany          #+#    #+#             */
/*   Updated: 2022/01/06 16:39:05 by letumany         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	copy_line(char **remind, char **line, int fd)
{
	int		i;
	char	*ptr;

	i = 0;
	while (remind[fd][i] != '\n' && remind[fd][i] != '\0')
		i++;
	*line = (char *)malloc(i + 1);
	if (!(*line))
		return (-1);
	ft_strncpy(*line, remind[fd], i + 1);
	ptr = ft_strchr(remind[fd], '\n');
	if (ptr)
	{
		ptr = ft_strdup(ptr + 1);
		free(remind[fd]);
		remind[fd] = ptr;
		return (1);
	}
	free(remind[fd]);
	remind[fd] = NULL;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*remind[4096];
	int			nbytes;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!line || fd < 0 || !buffer || BUFFER_SIZE <= 0)
		return (-1);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		nbytes = ft_strlen(buffer);
		buffer[nbytes] = '\0';
		if (!remind[fd])
			remind[fd] = ft_strdup(buffer);
		else
			remind[fd] = ft_strjoin(remind[fd], buffer);
		if (ft_strchr(remind[fd], '\n'))
			break ;
	}
	free(buffer);
	if (nbytes < 0)
		return (-1);
	else if (nbytes > 0 || (nbytes == 0 && remind[fd]))
		return (copy_line(remind, line, fd));
	*line = ft_strdup("");
	return (0);
}
