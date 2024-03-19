/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:02:24 by woorikim          #+#    #+#             */
/*   Updated: 2024/03/19 16:31:44 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static double	calc_delta_dist(double dir_self, double dir_other)
{
	if (dir_other == 0)
		return (0);
	if (dir_self == 0)
		return (1);
	return (fabs(1 / dir_self));
}

static void	calc_step_side_dist(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player->pos_x - ray->hit_x) * \
			ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->hit_x + 1.0 - game->player->pos_x) * \
			ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player->pos_y - ray->hit_y) * \
			ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->hit_y + 1.0 - game->player->pos_y) * \
			ray->delta_dist_y;
	}
}

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->cam_x = (2 * x / (double)WIN_WIDTH) - 1;
	ray->ray_dir_x = game->player->dir_x + game->player->pln_x * ray->cam_x;
	ray->ray_dir_y = game->player->dir_y + game->player->pln_y * ray->cam_x;
	ray->hit_x = (int)(game->player->pos_x);
	ray->hit_y = (int)(game->player->pos_y);
	ray->delta_dist_x = calc_delta_dist(ray->ray_dir_x, ray->ray_dir_y);
	ray->delta_dist_y = calc_delta_dist(ray->ray_dir_y, ray->ray_dir_x);
	ray->hit = 0;
	calc_step_side_dist(ray, game);
}
