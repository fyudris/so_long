/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:41:05 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 19:52:23 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

/**
 * @brief Appends new content to the existing buffer and frees the old buffer.
 *
 * This function concatenates the current buffer with the new content,
 * frees the old buffer, and returns the newly allocated buffer.
 *
 * @param buffer The current accumulated content.
 * @param new_content The newly read content to append.
 * @return A pointer to the newly allocated buffer containing the
 concatenated content.
 */
char	*append_and_free(char *buffer, char *new_content)
{
	char	*temp;

	temp = ft_strjoin(buffer, new_content);
	free(buffer);
	return (temp);
}

/**
 * @brief Extracts the remaining content after the first newline in the
 buffer.
 *
 * This function finds the first newline in the buffer and returns a newly
 allocated string containing everything after that newline. The original
 buffer is freed.
 *
 * @param buffer The current buffer containing file content.
 * @return A pointer to the remaining content after the first newline,
 *         or NULL if no newline is found.
 */
char	*extract_remaining(char *buffer)
{
	int		i;
	int		j;
	char	*remaining;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remaining = ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!remaining)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	while (buffer[i])
		remaining[j++] = buffer[i++];
	free(buffer);
	return (remaining);
}

/**
 * @brief Extracts the next line from the buffer.
 *
 * This function extracts characters from the buffer up to and including
 the first
 * newline character (if present) and returns them as a new string.
 The buffer itself is not modified.
 *
 * @param buffer The current buffer containing file content.
 * @return A newly allocated string containing the next line, or NULL
 if the buffer is empty.
 */
char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// FIX: Correctly allocate memory whether a newline is found or not.
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
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

/**
 * @brief Reads content from a file descriptor until a newline is encountered.
 *
 * This function reads from the given file descriptor in chunks of size
 BUFFER_SIZE,
 * appending the read data to the accumulated result until a newline character
 is encountered
 * or there is nothing left to read.
 *
 * @param fd The file descriptor to read from.
 * @param result The current accumulated content.
 * @return A pointer to the accumulated content, or NULL if an error occurs.
 */
char	*read_from_fd(int fd, char *result)
{
	char	*buffer;
	int		bytes_read;

	if (!result)
		result = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free (result);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		result = append_and_free(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free (buffer);
	return (result);
}

/**
 * @brief Retrieves the next line from a file descriptor.
 *
 * This function uses a static buffer to keep track of previously read
 content.
 * It reads from the file descriptor until a newline is encountered,
 extracts the next line from the buffer, updates the buffer with the remaining
 content, and returns the line.
 *
 * @param fd The file descriptor to read from.
 * @return The next line read from the file descriptor, or NULL if there is no
 more content or on error.
 */
char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	char		*line;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (0);
	// Only read from the file if the buffer for this fd doesn't already have a line.
	if (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
	{
		buffer[fd] = read_from_fd(fd, buffer[fd]);
	}
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = extract_remaining(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	return (line);
}
