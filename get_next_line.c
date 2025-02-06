/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhermini <mhermini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:09:34 by mhermini          #+#    #+#             */
/*   Updated: 2025/02/06 05:20:59 by mhermini         ###   ########.fr       */
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

static *free_buffer(char **buffer_stored, char **chunck)
{
	if (buffer_stored)
	{
		free(*buffer_stored);
		*buffer_stored = NULL;
	}
	if (chunck)
	{
		free(*chunck);
		*chunck = NULL;
	}
	return (NULL);
}

static char	*extract_line(char **buffer_stored)
{
	char	*ptr_newline_position;
	char	*extracted_line;
	char	*remaining_buffer;
	size_t	line_length;

	if (!buffer_stored || !(*buffer_stored))
		return (NULL);
	ptr_newline_position = ft_strchr(*buffer_stored, '\n');
	if (ptr_newline_position)
	{
		line_length = ptr_newline_position - *buffer_stored + 1;
		extracted_line = ft_substr(*buffer_stored, 0, line_length);
		remaining_buffer = ft_strdup(ptr_newline_position + 1);
	}
	else
	{
		extracted_line = ft_strdup(*buffer_stored);
		remaining_buffer = NULL;
	}
	free_buffer(buffer_stored, NULL);
	*buffer_stored = remaining_buffer;
	return (extracted_line);
}

static char	*handle_store(int fd, char *buffer_stored)
{
	char	*merged_buffer;
	char	*chunck;
	ssize_t	bytes_read;

	bytes_read = 1;
	if (!buffer_stored)
		buffer_stored = ft_calloc(1, sizeof(char));
	chunck = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	while (!(ft_strchr(buffer_stored, '\n') || bytes_read == 0))
	{
		bytes_read = read(fd, chunck, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_buffer(&buffer_stored, &chunck));
		chunck[bytes_read] = '\0';
		merged_buffer = ft_strjoin(buffer_stored, chunck);
		free_buffer(&buffer_stored, NULL);
		buffer_stored = merged_buffer;
	}
	free_buffer(NULL, &chunck);
	if ((*buffer_stored == '\0' || !buffer_stored) && bytes_read == 0)
		free_buffer(&buffer_stored, NULL);
	return (buffer_stored);
}

char	*get_next_line(int fd)
{
	static char	*buffer_stored;
	char		*current_line;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	buffer_stored = handle_store(fd, buffer_stored);
	if (!buffer_stored)
		return (NULL);
	current_line = extract_line(&buffer_stored);
	if (!current_line)
		return (free_buffer(&buffer_stored, NULL));
	return (current_line);
}
