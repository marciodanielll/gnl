/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhermini <mhermini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:09:34 by mhermini          #+#    #+#             */
/*   Updated: 2025/02/05 00:22:18 by mhermini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
		str++;
	return (str - s);
}

char	*free_buffer(char **buffer, char **read_buf)
{
	if (buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (read_buf)
	{
		free(*read_buf);
		*read_buf = NULL;
	}
	return (NULL);
}

char	*extract_line(char **buffer)
{
	char	*newline;
	char	*line;
	char	*new_buffer;
	size_t	len;

	if (!buffer || !(*buffer))
		return (NULL);
	newline = ft_strchr(*buffer, '\n');
	if (newline)
	{
		len = newline - *buffer + 1;
		line = ft_substr(*buffer, 0, len);
		new_buffer = ft_strdup(newline + 1);
	}
	else
	{
		line = ft_strdup(*buffer);
		new_buffer = NULL;
	}
	free_buffer(buffer, NULL);
	*buffer = new_buffer;
	return (line);
}

char	*read_and_store(int fd, char *stored_buffer)
{
	char	*new_buffer;
	char	*read_buffer;
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!stored_buffer)
		stored_buffer = ft_calloc(1, sizeof(char));
	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!ft_strchr(stored_buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_buffer(&stored_buffer, &read_buffer));
		read_buffer[bytes_read] = '\0';
		new_buffer = ft_strjoin(stored_buffer, read_buffer);
		free_buffer(&stored_buffer, NULL);
		stored_buffer = new_buffer;
	}
	free_buffer(&read_buffer, NULL);
	if ((*stored_buffer == '\0' || !stored_buffer) && bytes_read == 0)
		return (free_buffer(&stored_buffer, NULL));
	return (stored_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(&buffer);
	if (!line)
		return (free_buffer(&buffer, NULL));
	return (line);
}
