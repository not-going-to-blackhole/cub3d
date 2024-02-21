/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:18:28 by woorikim          #+#    #+#             */
/*   Updated: 2023/06/12 12:13:39 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save;
	char		*read_str;
	ssize_t		read_cnt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	read_cnt = read_string(read_str, &save, fd);
	if (read_cnt == -1)
		return (NULL);
	while (read_cnt > 0 || (read_cnt == 0 && ft_strchr_gnl(save, '\n') != 0))
	{
		if (joining(&save, read_str) == 0)
			return (NULL);
		if (get_a_line(&save, &read_str) == 1)
			return (read_str);
		read_cnt = read_string(read_str, &save, fd);
		if (read_cnt == -1)
			return (NULL);
	}
	free(read_str);
	return (get_remainder(&save));
}

ssize_t	read_string(char *read_str, char **save, int fd)
{
	ssize_t	read_cnt;

	if (read_str == NULL)
	{
		if (*save != NULL)
			free(*save);
		*save = NULL;
		return (-1);
	}
	read_cnt = read(fd, read_str, BUFFER_SIZE);
	if (read_cnt == -1)
	{
		free(read_str);
		if (*save != NULL)
			free(*save);
		*save = NULL;
		return (-1);
	}
	read_str[read_cnt] = '\0';
	return (read_cnt);
}

int	joining(char **save, char *read_str)
{
	char	*tmp_str;

	tmp_str = ft_strjoin_gnl(*save, read_str);
	if (*save)
	{
		free(*save);
		*save = NULL;
	}
	if (!tmp_str)
	{
		free(read_str);
		return (0);
	}
	*save = tmp_str;
	return (1);
}

int	get_a_line(char **save, char **read_str)
{
	long long int	nl_loc;

	nl_loc = ft_strchr_gnl(*save, '\n') - *save;
	if (nl_loc >= 0)
	{
		free(*read_str);
		*read_str = ft_strdup_gnl(*save, '\n');
		if (!*read_str)
		{
			if (*save)
			{
				free(*save);
				*save = NULL;
			}
		}
		else
			ft_strlcpy_gnl(*save, *save + nl_loc + 1);
		return (1);
	}
	else
		return (0);
}

char	*get_remainder(char **save)
{
	char	*res;

	res = NULL;
	if (*save)
	{
		res = ft_strdup_gnl(*save, '\0');
		free(*save);
		*save = NULL;
	}
	return (res);
}
