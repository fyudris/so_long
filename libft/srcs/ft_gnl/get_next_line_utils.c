/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fyudris <fyudris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:17:18 by fyudris           #+#    #+#             */
/*   Updated: 2025/06/13 19:52:30 by fyudris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

/**
 * @brief Computes the length of a string (excluding the null terminator).
 *
 * @param str A pointer to the null-terminated string.
 * @return The length of the string.
 */
size_t	ft_strlen(const char *str)
{
	const char	*s;

	s = str;
	while (*s)
		s++;
	return ((size_t)(s - str));
}

/**
 * @brief Sets the first n bytes of the memory area pointed to by s to zero.
 *
 * @param s A pointer to the memory area to fill.
 * @param n The number of bytes to be set to zero.
 */
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = 0;
}

/**
 * @brief Allocates memory for an array and initializes all bytes to zero.
 *
 * @param elem_count The number of elements to allocate.
 * @param elem_size The size in bytes of each element.
 * @return A pointer to the allocated memory, or NULL if the allocation fails.
 */
void	*ft_calloc(size_t elem_count, size_t elem_size)
{
	void	*ptr;

	ptr = malloc(elem_count * elem_size);
	if (ptr)
		ft_bzero(ptr, elem_count * elem_size);
	return (ptr);
}

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * @param s The null-terminated string to search.
 * @param c The character to locate (provided as an int but converted to char).
 * @return A pointer to the first occurrence of the character in s, or NULL
 if the character is not found.
 */
char	*ft_strchr(const char *string, int searchChar)
{
	char	*str;

	str = (char *)string;
	while (*str && *str != searchChar)
		str++;
	if (*str == searchChar)
		return (str);
	else
		return (NULL);
}

/**
 * @brief Concatenates two strings into a newly allocated string.
 *
 * @param s1 The first null-terminated string.
 * @param s2 The second null-terminated string.
 * @return A pointer to the newly allocated concatenated string,
 or NULL on error.
 */
char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*result;
	char	*temp;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	temp = result;
	while (*s1)
		*temp++ = *s1++;
	while (*s2)
		*temp++ = *s2++;
	*temp = '\0';
	return (result);
}
