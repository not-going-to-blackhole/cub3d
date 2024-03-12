#include "cub3d.h"

void    do_render(t_game *game)
{
    fill_background(game);
    draw_walls(game);
}

void    fill_background(t_game *game)
{
    int x;
    int y;

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

// raycasting
void    draw_walls(t_game *game)
{
    t_ray   ray;
    int     x;

    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray(game, &ray, x);
        calc_ray(game, &ray);
        calc_wall_height(game, &ray);
        draw_wall(game, &ray, x);
        x++;
    }

}

void    init_ray(t_game *game, t_ray *ray, int x)
{
    ray->cam_x = 2 * x / (double)WIN_WIDTH - 1; //카메라 x좌표 -1 / 1
    ray->ray_dir_x = game->player->dir_x + game->player->pln_x * ray->cam_x;
    ray->ray_dir_y = game->player->dir_y + game->player->pln_y * ray->cam_x;
    ray->hit = 0;
    ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}