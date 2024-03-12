#include "cub3d.h"

void	move_left(t_game *game)
{
	if (game->map_2d[(int)(game->player->pos_x - game->player->pln_x * MOV_SPEED)][(int)(game->player->pos_y)] != '1')
		game->player->pos_x -= game->player->pln_x * MOV_SPEED;
	if (game->map_2d[(int)(game->player->pos_x)][(int)(game->player->pos_y - game->player->pln_y * MOV_SPEED)] != '1')
		game->player->pos_y -= game->player->pln_y * MOV_SPEED;
}

void	move_right(t_game *game)
{
	if (game->map_2d[(int)(game->player->pos_x + game->player->pln_x * MOV_SPEED)][(int)(game->player->pos_y)] != '1')
		game->player->pos_x += game->player->pln_x * MOV_SPEED;
	if (game->map_2d[(int)(game->player->pos_x)][(int)(game->player->pos_y + game->player->pln_y * MOV_SPEED)] != '1')
		game->player->pos_y += game->player->pln_y * MOV_SPEED;
}

void	move_forward(t_game *game)
{
	if (game->map_2d[(int)(game->player->pos_x + game->player->dir_x * MOV_SPEED)][(int)(game->player->pos_y)] != '1')
		game->player->pos_x += game->player->dir_x * MOV_SPEED;
	if (game->map_2d[(int)(game->player->pos_x)][(int)(game->player->pos_y + game->player->dir_y * MOV_SPEED)] != '1')
		game->player->pos_y += game->player->dir_y * MOV_SPEED;
}

void	move_back(t_game *game)
{
	if (game->map_2d[(int)(game->player->pos_x - game->player->dir_x * MOV_SPEED)][(int)(game->player->pos_y)] != '1')
		game->player->pos_x -= game->player->dir_x * MOV_SPEED;
	if (game->map_2d[(int)(game->player->pos_x)][(int)(game->player->pos_y - game->player->dir_y * MOV_SPEED)] != '1')
		game->player->pos_y -= game->player->dir_y * MOV_SPEED;
}