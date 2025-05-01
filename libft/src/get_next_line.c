/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: w0ffel <w0ffel@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/31 15:26:26 by w0ffel        #+#    #+#                 */
/*   Updated: 2025/01/17 17:48:31 by w0ffel        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_next(char *buffer)
{
	char	*next_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	next_line = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!next_line)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
		next_line[j++] = buffer[i++];
	next_line[j] = '\0';
	free(buffer);
	return (next_line);
}

char	*ft_line(char	*buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + (buffer[i] == '\n') + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

int	ft_read_loop(int fd, char **str, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*str);
			*str = NULL;
			return (-1);
		}
		buffer[bytes_read] = 0;
		*str = ft_join_and_free(*str, buffer);
		if (!(*str))
			return (-1);
		if (ft_strchr(*str, '\n'))
			break ;
	}
	return (bytes_read);
}

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(str), NULL);
	if (!str)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (free(buffer), NULL);
	}
	bytes_read = ft_read_loop(fd, &str, buffer);
	free(buffer);
	if (bytes_read == 0 && *str == 0)
		return (free(str), NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = ft_read(fd, leftover);
	if (!leftover)
		return (NULL);
	line = ft_line(leftover);
	if (!line || !*line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	leftover = ft_next(leftover);
	if (!leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (line);
}
