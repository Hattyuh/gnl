/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkosa <rkosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:52:29 by rkosa             #+#    #+#             */
/*   Updated: 2026/07/13 17:39:42 by rkosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*add_to_stash(int fd, char *content, int *bytes)
{
	char	*buffer;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes <= 0)
		return (free(buffer), NULL);
	content = malloc(*bytes + 1);
	if (!content)
		return (free(buffer), NULL);
	ft_memcpy(content, buffer, *bytes);
	content[*bytes] = '\0';
	return (free(buffer), content);
}

char	*append_stash(int fd, char *content, int *bytes)
{
	char	*buffer;
	char	*new_content;
	size_t	len;

	if (!content)
		return (add_to_stash(fd, content, bytes));
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (free(content), NULL);
	*bytes = read(fd, buffer, BUFFER_SIZE);
	new_content = NULL;
	len = ft_strlen(content);
	if (*bytes < 0)
		return (free(buffer), free(content), NULL);
	if (*bytes == 0)
		return (free(buffer), content);
	new_content = malloc(len + *bytes + 1);
	if (!new_content)
		return (free(buffer), free(content), NULL);
	ft_memcpy(new_content, content, len);
	free(content);
	ft_memcpy(&new_content[len], buffer, *bytes);
	new_content[len + *bytes] = '\0';
	return (free(buffer), new_content);
}

char	*save_line(char *stash)
{
	char	*line;
	size_t	len;

	line = NULL;
	if (!stash || !stash[0])
		return (line);
	if (get_line_end(stash))
		len = ft_linelen(stash);
	else
		len = ft_strlen(stash);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

char	*mod_stash(char *stash, int *bytes)
{
	char	*new_stash;
	char	*temp;
	size_t	len;

	if (!stash)
		return (NULL);
	if (!*bytes)
		return (free(stash), NULL);
	temp = get_line_end(stash);
	if (!temp)
		return (free(stash), NULL);
	temp++;
	len = ft_strlen(temp);
	if (len == 0)
		return (free(stash), NULL);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (free(stash), NULL);
	ft_memcpy(new_stash, temp, len);
	new_stash[len] = '\0';
	return (free(stash), new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			bytes;
	char		*line;

	line = NULL;
	bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (bytes > 0 && !get_line_end(stash))
	{
		stash = append_stash(fd, stash, &bytes);
		if (!stash)
			return (NULL);
	}
	line = save_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = mod_stash(stash, &bytes);
	return (line);
}
