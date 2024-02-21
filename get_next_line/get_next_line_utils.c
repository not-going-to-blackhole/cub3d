/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:18:31 by woorikim          #+#    #+#             */
/*   Updated: 2023/06/08 12:24:31 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s, int c)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (len);
	while (*s != c && *s++)
		len++;
	return (len);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlcpy_gnl(char *dest, const char *src)
{
	size_t	src_size;
	size_t	i;

	src_size = ft_strlen_gnl(src, '\0');
	i = 0;
	while (i <= src_size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_size);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	total_len;

	total_len = ft_strlen_gnl(s1, '\0') + ft_strlen_gnl(s2, '\0');
	new_str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_str)
		return (0);
	i = 0;
	if (s1 != NULL)
	{
		while (s1[i])
		{
			new_str[i] = s1[i];
			i++;
		}
	}
	if (s2 != NULL)
	{
		while (*s2)
			*(new_str + (i++)) = *s2++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_strdup_gnl(const char *src, int c)
{
	char	*dest;
	int		len;
	int		i;

	len = ft_strlen_gnl(src, c);
	if (len == 0 && c == '\0')
		return (0);
	i = 0;
	if (c == '\n')
		len++;
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
	{
		return (0);
	}
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
