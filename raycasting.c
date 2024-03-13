#include "cub3d.h"

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
