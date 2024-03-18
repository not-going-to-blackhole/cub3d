/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:02:17 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 00:18:14 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_error(const char *tmp)
{
	write(2, tmp, counting_str_length(tmp));
	exit(FAIL);
}

char	**all_free(char **wd)
{
	int	i;

	i = 0;
	while (wd[i])
	{
		free(wd[i]);
		i++;
	}
	free(wd);
	return (0);
}