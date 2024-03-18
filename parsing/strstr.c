/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:15:09 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 00:18:46 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*duplicate_string(const char *str)
{
	char	*tmp;
	int		i;
	int		count;

	i = 0;
	count = counting_str_length(str);
	tmp = (char *)malloc(count * sizeof(char) + 1);
	if (!tmp)
		return (0);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char	*remove_new_line(char *line)
{
	int		i;
	char	*no_newline;

    i = 0;
	if (!line)
		return (NULL);
	no_newline = (char *)malloc(sizeof(char) * (counting_str_length(line) + 1));
	while (line[i])
	{
		no_newline[i] = line[i];
		if (line[i] == '\n')
			break ;
		i++;
	}
	no_newline[i] = '\0';
	return (no_newline);
}
