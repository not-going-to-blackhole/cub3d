/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:02:17 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 16:38:38 by woorikim         ###   ########.fr       */
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
