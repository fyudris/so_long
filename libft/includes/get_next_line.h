/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:44:55 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/17 03:27:08 by fyudris          ###   ########.fr       */
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

size_t	ft_strlen_gnl(const char *str);
void	*ft_calloc_gnl(size_t elem_count, size_t elem_size);
char	*ft_strchr_gnl(const char *string, int searchChar);
char	*ft_strjoin_gnl(const char *s1, const char *s2);
void	ft_bzero_gnl(void *s, size_t n);

#endif
