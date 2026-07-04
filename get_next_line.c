/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkosa <rkosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:52:29 by rkosa             #+#    #+#             */
/*   Updated: 2026/06/30 14:49:23 by rkosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*add_to_stash(int fd, char *content, int *bytes)
{
	char	buffer[BUFFER_SIZE];

	*bytes = read(fd, buffer, BUFFER_SIZE);
	if (*bytes < 0)
		return (NULL);
	if (*bytes == 0)
		return (content);
	content = malloc(*bytes + 1);
	if (!content)
		return (NULL);
	ft_memcpy(content, buffer, *bytes);
	content[*bytes] = '\0';
	return (content);
}

char	*append_stash(int fd, char *content, int *bytes)
{
	char	buffer[BUFFER_SIZE];
	char	*new_content;
	size_t	len;

	if (!content)
		return (add_to_stash(fd, content, bytes));
	*bytes = read(fd, buffer, BUFFER_SIZE);
	new_content = NULL;
	len = ft_strlen(content);
	if (*bytes < 0)
		return (NULL);
	if (*bytes == 0)
		return (content);
	new_content = malloc(len + *bytes + 1);
	if (!new_content)
		return (NULL);
	ft_memcpy(new_content, content, len);
	free(content);
	ft_memcpy(&new_content[len], buffer, *bytes);
	new_content[len + *bytes] = '\0';
	return (new_content);
}

char	*save_line(char *stash)
{
	char	*line;
	size_t	len;

	line = NULL;
	if (!stash)
		return (line);
	if (get_line_end(stash))
		len = ft_linelen(stash);
	else
		len = ft_strlen(stash);
	line = malloc(len + 1);
	ft_memcpy(line, stash, len);
	line[len] = '\0';
	return (line);
}

char	*mod_stash(char *stash, int *bytes)
{
	char	*new_stash;
	char	*temp;
	size_t	len;

	if (!*bytes)
	{
		free(stash);
		return (NULL);
	}
	temp = get_line_end(stash);
	if (temp)
		len = ft_strlen(temp++);
	else
		len = ft_strlen(stash);
	if (len == 0)
		return (NULL);
	new_stash = malloc(len + 1);
	if (!new_stash)
		return (NULL);
	ft_memcpy(new_stash, temp, len);
	free(stash);
	new_stash[len] = '\0';
	return (new_stash);
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
		stash = append_stash(fd, stash, &bytes);
	line = save_line(stash);
	stash = mod_stash(stash, &bytes);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// #include "get_next_line.h"

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		count;

// 	fd = open("test.txt", O_RDONLY);
// 	count = 0;
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		++count;
// 		printf("[LINE %d]: %s\n\n", count, line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
