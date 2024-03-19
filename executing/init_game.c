/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:20:21 by woorikim          #+#    #+#             */
/*   Updated: 2024/03/19 16:41:17 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_player(t_game *game, int i, int j)
{
	game->player->pos_x = i + 0.5;
	game->player->pos_y = j + 0.5;
	if (game->map_2d[i][j] == 'N')
	{
		game->player->dir_x = -1;
		game->player->pln_y = 0.66;
	}
	else if (game->map_2d[i][j] == 'S')
	{
		game->player->dir_x = 1;
		game->player->pln_y = -0.66;
	}
	else if (game->map_2d[i][j] == 'W')
	{
		game->player->dir_y = -1;
		game->player->pln_x = -0.66;
	}
	else if (game->map_2d[i][j] == 'E')
	{
		game->player->dir_y = 1;
		game->player->pln_x = 0.66;
	}
	else
		return (0);
	return (1);
}

void	init_player(t_game *game)
{
	int	i;
	int	j;

	game->player->pln_x = 0;
	game->player->pln_y = 0;
	game->player->dir_x = 0;
	game->player->dir_y = 0;
	i = 0;
	while (game->map_2d[i])
	{
		j = 0;
		while (game->map_2d[i][j])
		{
			if (set_player(game, i, j) == 1)
				return ;
			j++;
		}
		i++;
	}
}

static void	init_text(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].path = NULL;
		game->texture[i].img = NULL;
		game->texture[i].data = NULL;
		i++;
	}
}

void	init_game(t_game *game, char *file)
{
	game->map = NULL;
	game->map_2d = NULL;
	game->map_height = 0;
	game->player_cnt = 0;
	game->file_fd = open(file, O_RDONLY);
	if (game->file_fd < 0)
		print_error("Error\nopen file\n");
	game->color = (t_color *)malloc(sizeof(t_color));
	game->player = (t_player *)malloc(sizeof(t_player));
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->color || !game->player || !game->img)
	{
		print_error("Error\nmalloc\n");
		exit(1);
	}
	init_text(game);
	game->color->c_valid = 0;
	game->color->f_valid = 0;
}

void	init_pixel(t_game *game)
{
	int	i;
	int	j;

	game->pixels = (int **)malloc(sizeof(int *) * WIN_HEIGHT);
	if (!game->pixels)
		print_error("Error\nmalloc\n");
	i = 0;
	while (i < WIN_HEIGHT)
	{
		game->pixels[i] = (int *)malloc(sizeof(int) * WIN_WIDTH);
		if (!game->pixels[i])
			print_error("Error\nmalloc\n");
		i++;
	}
	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			game->pixels[i][j] = 0;
			j++;
		}
		i++;
	}
}
