/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhermini <mhermini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 23:13:15 by mhermini          #+#    #+#             */
/*   Updated: 2025/02/05 01:50:54 by mhermini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (nmemb == 0 || size == 0)
	{
		ptr = (void *)malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb && (size > (((size_t)-1) / nmemb)))
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	while (total_size--)
		((char *)ptr)[total_size] = 0;
	return (ptr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned char	*ptr;
	unsigned char	*ptr_original;
	size_t			size_s1;
	size_t			size_s2;
	size_t			total_size;

	size_s1 = ft_strlen(s1) * sizeof(char);
	size_s2 = ft_strlen(s2) * sizeof(char);
	total_size = size_s1 + size_s2 + 1;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ptr_original = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return ((char *)ptr_original);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*original_ptr;
	size_t	total_size;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	total_size = (len + 1) * sizeof(char);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	original_ptr = ptr;
	s += start;
	while (len--)
		*ptr++ = *s++;
	*ptr = '\0';
	return (original_ptr);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*original_dup;
	size_t	total_size;

	total_size = (ft_strlen(s) + 1) * sizeof(char);
	dup = malloc(total_size);
	if (!dup)
		return (NULL);
	original_dup = dup;
	while (--total_size)
		*dup++ = *s++;
	*dup = '\0';
	return (original_dup);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	index;
	size_t	length;

	if (!s)
		return (NULL);
	length = ft_strlen(s);
	if (c == '\0')
		return ((char *)&s[length]);
	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (unsigned char)c)
			return ((char *)&s[index]);
		index++;
	}
	return (NULL);
}
