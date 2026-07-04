/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkosa <rkosa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 18:52:32 by rkosa             #+#    #+#             */
/*   Updated: 2026/06/29 18:36:19 by rkosa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_line_end(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *str);
size_t	ft_linelen(const char *str);

char	*get_next_line(int fd);
char	*add_to_stash(int fd, char *content, int *bytes);
char	*append_stash(int fd, char *content, int *bytes);
char	*save_line(char *stash);
char	*mod_stash(char *stash, int *bytes);

#endif
