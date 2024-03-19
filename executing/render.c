/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:08:03 by woorikim          #+#    #+#             */
/*   Updated: 2024/03/19 16:09:25 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	fill_background(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT / 2)
		{
			game->pixels[y][x] = game->color->c_bit_rgb;
			game->pixels[WIN_HEIGHT - y - 1][x] = game->color->f_bit_rgb;
			y++;
		}
		x++;
	}
}

static void	find_walls(t_game *game)
{
	t_ray		ray;
	t_render	render;
	int			x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(game, &ray, x);
		perform_ray(game, &ray);
		calc_wall(game, &ray);
		set_texture(game, &ray, &render);
		paint_wall(game, &ray, &render, x);
		x++;
	}
}

static void	render_window(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			game->img->data[y * WIN_WIDTH + x] = game->pixels[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
}

void	do_render(t_game *game)
{
	fill_background(game);
	find_walls(game);
	render_window(game);
}
