/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 17:00:36 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/20 15:01:19 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static long	find_first_newline_index(char *map)
{
	long	i;

	i = 0;
	while (map[i])
	{
		if (map[i] != '\n')
			break ;
		i++;
	}
	return (i);
}

static char	*check_newlines_error(char	*map)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = duplicate_string(map);
	while (tmp[j])
	{
		if (tmp[j] == '\n')
			if (tmp[j + 1] == '\n' && tmp[j] != '\0' && tmp[j + 1])
				print_error("Error\nMap error\n");
		j++;
	}
	return (tmp);
}

void	map_validator(t_game *game)
{
	int		height;
	char	**map_2d;
	char	*copy_map;
	long	location;

	height = 0;
	if (game->player_cnt >= 2 || game->player_cnt == 0)
		print_error("Error\nPlayer count error\n");
	location = find_first_newline_index(game->map);
	copy_map = check_newlines_error(game->map + location);
	map_2d = parsing_str(copy_map, '\n');
	if (map_2d == (void *)0)
		print_error("Error\nMap malloc fail\n");
	checking_map2(map_2d);
	checking_wall(map_2d);
	game->map_2d = map_2d;
	while (game->map_2d[height])
		height++;
	game->map_height = height;
	free(copy_map);
	free(game->map);
}
