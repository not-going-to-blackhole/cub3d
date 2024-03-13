#include "cub3d.h"

static void    fill_background(t_game *game)
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
static void    find_walls(t_game *game)
{
    t_ray   ray;
    t_render    render;
    int     x;

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

static void    render_window(t_game *game)
{
    int x;
    int y;

    x = 0;
    while (x < WIN_WIDTH)
    {
        y = 0;
        while (y < WIN_HEIGHT)
        {
            game->img->data[y * WIN_WIDTH + x] = game->pixels[y][x];
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
}

void    do_render(t_game *game)
{
    fill_background(game);
    find_walls(game);
    render_window(game);
}