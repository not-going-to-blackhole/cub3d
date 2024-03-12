#include "cub3d.h"

void    do_render(t_game *game)
{
    fill_background(game);
    draw_walls(game);
    render_window(game);
}

void    render_window(t_game *game)
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

// delta_dist 공식
int calc_delta_dist(double dir_self, double dir_other)
{
    if (dir_other == 0)
        return (0);
    else if (dir_self == 0)
        return (1);
    else
        return (fabs(1 / dir_self));
}

//init step, side_dist
void calc_step_side_dist(t_ray *ray, t_game *game)
{
    if (ray->ray_dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (game->player->pos_x - ray->hit_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->hit_x + 1.0 - game->player->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (game->player->pos_y - ray->hit_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->hit_y + 1.0 - game->player->pos_y) * ray->delta_dist_y;
    }
}

void    init_ray(t_game *game, t_ray *ray, int x)
{
    ray->cam_x = 2 * x / (double)WIN_WIDTH - 1; //카메라 x좌표 -1 / 1
    //ray의 방향벡터 계산
    ray->ray_dir_x = game->player->dir_x + game->player->pln_x * ray->cam_x;
    ray->ray_dir_y = game->player->dir_y + game->player->pln_y * ray->cam_x;
    ray->hit = 0;
    ray->hit_x = (int)game->player->pos_x;
    ray->hit_y = (int)game->player->pos_y;
    ray->delta_dist_x = calc_delta_dist(ray->ray_dir_x, ray->ray_dir_y);
    ray->delta_dist_y = calc_delta_dist(ray->ray_dir_y, ray->ray_dir_x);
    calc_step_side_dist(ray, game);
}

void    perform_ray(t_game *game, t_ray *ray)
{
    while (ray->hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->hit_x += ray->step_x;
            ray->side = WALL_HORIZ;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->hit_y += ray->step_y;
            ray->side = WALL_VERT;
        }
        if (game->map_2d[ray->hit_x][ray->hit_y] == '1')
            ray->hit = 1;
    }
}

void    calc_wall(t_game *game, t_ray *ray)
{
    // 벽까지의 거리 계산
    if (ray->side == WALL_HORIZ)
        ray->perp_wall_dist = (ray->hit_x - game->player->pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
    else
        ray->perp_wall_dist = (ray->hit_y - game->player->pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
    // 벽까지의 거리에 따라 높이 계산
    ray->wall_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
    // 벽을 그리기 위한 시작점과 끝점 계산
    ray->wall_start = -ray->wall_height / 2 + WIN_HEIGHT / 2;
    if (ray->wall_start < 0)
        ray->wall_start = 0;
    ray->wall_end = ray->wall_height / 2 + WIN_HEIGHT / 2;
    if (ray->wall_end >= WIN_HEIGHT)
        ray->wall_end = WIN_HEIGHT - 1;
}

void    set_texture(t_game *game, t_ray *ray, t_render *render)
{
    if (ray->side == WALL_HORIZ)
        render->wall_x = game->player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else
        render->wall_x = game->player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    render->wall_x -= floor(render->wall_x);
    render->text_x = (int)(render->wall_x * (double)TILE_SIZE);
    if (ray->side == WALL_HORIZ && ray->ray_dir_x > 0)
        render->text_x = TILE_SIZE - render->text_x - 1;
    if (ray->side == WALL_VERT && ray->ray_dir_y < 0)
        render->text_x = TILE_SIZE - render->text_x - 1;
    if (ray->side == WALL_HORIZ)
    {
        render->text_idx = NO;
        if (ray->ray_dir_x > 0)
            render->text_idx = SO;
    }
    else
    {
        render->text_idx = WE;
        if (ray->ray_dir_y > 0)
            render->text_idx = EA;
    }
}

void    paint_wall(t_game *game, t_ray *ray, t_render *render, int x)
{
    int y;

    y = ray->wall_start;
    render->step = 1.0 * TILE_SIZE / ray->wall_height;
    render->pos = (ray->wall_start - WIN_HEIGHT / 2 + ray->wall_height / 2) * render->step;
    while (y < ray->wall_end)
    {
        render->text_y = (int)render->pos & (TILE_SIZE - 1);
        render->pos += render->step;
        render->color = game->texture[render->text_idx].data[TILE_SIZE * render->text_y + render->text_x];
        if (ray->side == WALL_VERT)
            render->color = (render->color >> 1) & 8355711;
        game->pixels[y][x] = render->color;
        y++;
    }
}