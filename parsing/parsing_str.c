/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 22:31:36 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 02:35:03 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_str(char str1, char str2)
{
	if (str1 == str2)
		return (1);
	return (0);
}

static int	malloc_cnt(char const *str1, char str2)
{
	int	i;
	int	cnt;

    i = 0;
	cnt = 0;
	while (str1[i] != '\0')
	{
		while (str1[i] && (check_str(str1[i], str2) == 1))
			i++;
		if (str1[i])
		{
			cnt++;
			i++;
		}
		while (str1[i] && (check_str(str1[i], str2) == 0))
			i++;
	}
	return (cnt);
}

static char	*input_word(char const *str1, char str2)
{
	int		i;
    int		j;
	int		cnt;
    char	*tmp;

    i = 0;
	j = 0;
	cnt = 0;
	while (str1[i] != '\0' && check_str(str1[i], str2) == 0)
	{
		i++;
		cnt++;
	}
	tmp = (char *)malloc(sizeof(char) * cnt + 1);
	if (!tmp)
		return (0);
	while (str1[j] != '\0' && check_str(str1[j], str2) == 0)
	{
		tmp[j] = str1[j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}

char	**parsing_str(char const *str1, char str2)
{
	char	**tmp;
	int		cnt;
	int		size;

	cnt = 0;
	size = malloc_cnt(str1, str2);
	tmp = (char **)malloc(sizeof(char *) * (size + 1));
	if (!tmp)
		return (0);
	while (*str1)
	{
		while (*str1 && check_str(*str1, str2) == 1)
			str1++;
		if (*str1)
		{
			tmp[cnt++] = input_word(str1, str2);
			if (tmp[cnt - 1] == 0)
				return (all_free(tmp));
			str1++;
		}
		while (*str1 && (check_str(*str1, str2) == 0))
			str1++;
	}
	tmp[cnt] = 0;
	return (tmp);
}
