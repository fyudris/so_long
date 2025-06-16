/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:44:55 by fyudris           #+#    #+#             */
/*   Updated: 2025/02/11 15:23:38 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_from_fd(int fd, char *result);
char	*extract_line(char *buffer);
char	*extract_remaining(char *buffer);
char	*append_and_free(char *buffer, char *new_content);

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t elem_count, size_t elem_size);
char	*ft_strchr(const char *string, int searchChar);
char	*ft_strjoin(const char *s1, const char *s2);

#endif
