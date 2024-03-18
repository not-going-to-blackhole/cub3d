/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:01:00 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 00:17:06 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	counting_str_length(char const *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

long	check_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if ('0' <= str[i] && str[i] <= '9')
			res = (10 * res) + str[i] - '0';
		else
			error("Error : atoi invalid\n");
		i++;
	}
	if (i >= 11)
		error("Error : Invaild range(long long)\n");
	return (res);
}

int	str_ncompare(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}

int	mini_atoi(char *str)
{
	int i;
	int res;

	i = 0;
    res = check_atoi((str + i));
	if (str[i] == '-')
		error("Error : Invaild_int\n");
	if (!((0 <= res) && (res <= 255)))
		error("Error : Invaild atoi range\n");
	return (res);
}
