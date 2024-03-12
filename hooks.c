#include "cub3d.h"

static void	turn_left(t_game *game)
{
	double	prev_dir_x;
	double	prev_pln_x;

	prev_dir_x = game->player->dir_x;
	prev_pln_x = game->player->pln_x;
	game->player->dir_x = game->player->dir_x * cos(ROT_SPEED) - game->player->dir_y * sin(ROT_SPEED);
	game->player->dir_y = prev_dir_x * sin(ROT_SPEED) + game->player->dir_y * cos(ROT_SPEED);
	game->player->pln_x = game->player->pln_x * cos(ROT_SPEED) - game->player->pln_y * sin(ROT_SPEED);
	game->player->pln_y = prev_pln_x * sin(ROT_SPEED) + game->player->pln_y * cos(ROT_SPEED);
}

static void	turn_right(t_game *game)
{
	double	prev_dir_x;
	double	prev_pln_x;

	prev_dir_x = game->player->dir_x;
	prev_pln_x = game->player->pln_x;
	game->player->dir_x = game->player->dir_x * cos(-ROT_SPEED) - game->player->dir_y * sin(-ROT_SPEED);
	game->player->dir_y = prev_dir_x * sin(-ROT_SPEED) + game->player->dir_y * cos(-ROT_SPEED);
	game->player->pln_x = game->player->pln_x * cos(-ROT_SPEED) - game->player->pln_y * sin(-ROT_SPEED);
	game->player->pln_y = prev_pln_x * sin(-ROT_SPEED) + game->player->pln_y * cos(-ROT_SPEED);
}

int	exit_game(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}


int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		exit_game(game);
	else if (key == KEY_W)
		move_forward(game);
	else if (key == KEY_A)
		move_left(game);
	else if (key == KEY_S)
		move_back(game);
	else if (key == KEY_D)
		move_right(game);
	else if (key == KEY_LEFT)
		turn_left(game);
	else if (key == KEY_RIGHT)
		turn_right(game);
	else
		return (0);
	do_render(game);
	return (0);
}

