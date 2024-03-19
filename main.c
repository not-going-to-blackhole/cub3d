#include "cub3d.h"

static int	check_av(char *av)
{
	int		str;
	int		tmp_cnt;
	char	**tmp;

	tmp_cnt = 0;
	tmp = parsing_str(av, '/');
	if (!tmp)
		print_error("Error : split argv\n");
	while (tmp[tmp_cnt])
		tmp_cnt++;
	tmp_cnt--;
	str = counting_str_length(tmp[tmp_cnt]);
	if (str <= 4)
		return (all_free(tmp), 1);
	if (!(tmp[tmp_cnt][str - 1] == 'b' && \
		tmp[tmp_cnt][str - 2] == 'u' \
		&& tmp[tmp_cnt][str - 3] == 'c' \
		&& tmp[tmp_cnt][str - 4] == '.'))
		return (all_free(tmp), 1);
	return (all_free(tmp), 0);
}

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

static void	init_player(t_game *game)
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

// static void	init_game_tmp(t_game *game, char *file)
// {
// 	game->mlx = mlx_init();
// 	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
// 	game->file_fd = open(file, O_RDONLY);
// 	game->map = NULL;
// 	game->map_height = 5;
// 	game->map_2d = (char **)malloc(sizeof(char *) * (game->map_height + 1));
// 	int i = 0;
// 	char *line;
// 	while (i < game->map_height)
// 	{
// 		line = get_next_line(game->file_fd);
// 		//printf("%s", line);
// 		game->map_2d[i] = line;
// 		i++;
// 	}
// 	game->map_2d[i] = NULL;
// 	close(game->file_fd);
// 	game->player = (t_player *)malloc(sizeof(t_player));
// 	init_player(game);
// 	game->color = (t_color *)malloc(sizeof(t_color));
// 	game->color->c_rgb[0] = 255;
// 	game->color->c_rgb[1] = 0;
// 	game->color->c_rgb[2] = 255;
// 	game->color->f_rgb[0] = 0;
// 	game->color->f_rgb[1] = 255;
// 	game->color->f_rgb[2] = 0;
// 	game->color->c_bit_rgb = (game->color->c_rgb[0] << 16 ) | (game->color->c_rgb[1] << 8) | game->color->c_rgb[2];
// 	game->color->f_bit_rgb = (game->color->f_rgb[0] << 16 ) | (game->color->f_rgb[1] << 8) | game->color->f_rgb[2];
// 	game->pixels = (int **)malloc(sizeof(int *) * WIN_HEIGHT);
// 	i = 0;
// 	while (i < WIN_HEIGHT)
// 	{
// 		game->pixels[i] = (int *)malloc(sizeof(int) * WIN_WIDTH);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < WIN_HEIGHT)
// 	{
// 		int j = 0;
// 		while (j < WIN_WIDTH)
// 		{
// 			game->pixels[i][j] = 0;
// 			j++;
// 		}
// 		i++;
// 	}
// 	int width;
// 	int height;
// 	game->img = (t_img *)malloc(sizeof(t_img));
// 	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
// 	game->img->data = (int *)mlx_get_data_addr(game->img->img, &game->img->pixel_bits, &game->img->line_len, &game->img->endian);
// 	game->texture[NO].img = mlx_xpm_file_to_image(game->mlx, "./texture/wall.xpm", &width, &height);
// 	game->texture[NO].data = (int *)mlx_get_data_addr(game->texture[NO].img, &game->texture[NO].pixel_bits, &game->texture[NO].line_len, &game->texture[NO].endian);
// 	game->texture[NO].path = "./texture/wall.xpm";
// 	game->texture[SO].img = mlx_xpm_file_to_image(game->mlx, "./texture/wall.xpm", &width, &height);
// 	game->texture[SO].data = (int *)mlx_get_data_addr(game->texture[SO].img, &game->texture[SO].pixel_bits, &game->texture[SO].line_len, &game->texture[SO].endian);
// 	game->texture[SO].path = "./texture/wall.xpm";
// 	game->texture[WE].img = mlx_xpm_file_to_image(game->mlx, "./texture/wall.xpm", &width, &height);
// 	game->texture[WE].data = (int *)mlx_get_data_addr(game->texture[WE].img, &game->texture[WE].pixel_bits, &game->texture[WE].line_len, &game->texture[WE].endian);
// 	game->texture[WE].path = "./texture/wall.xpm";
// 	game->texture[EA].img = mlx_xpm_file_to_image(game->mlx, "./texture/wall.xpm", &width, &height);
// 	game->texture[EA].data = (int *)mlx_get_data_addr(game->texture[EA].img, &game->texture[EA].pixel_bits, &game->texture[EA].line_len, &game->texture[EA].endian);
// 	game->texture[EA].path = "./texture/wall.xpm";
// 	game->player_cnt = 1;
// }

void	init_text(t_game *game)
{
	int i;

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
		print_error("Error : open file\n");
	game->color = (t_color *)malloc(sizeof(t_color));
	game->player = (t_player *)malloc(sizeof(t_player));
	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->color || !game->player || !game->img)
	{
		print_error("Error : malloc\n");
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
		print_error("Error : malloc\n");
	i = 0;
	while (i < WIN_HEIGHT)
	{
		game->pixels[i] = (int *)malloc(sizeof(int) * WIN_WIDTH);
		if (!game->pixels[i])
			print_error("Error : malloc\n");
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

void	check_text_rgb(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->color->c_rgb[i] != game->color->f_rgb[i])
			return ;
		i++;
	}
	print_error("Error : same color\n");
}

void	check_text_dir(char *path1, char *path2)
{
	if (!str_ncompare(path1, path2, counting_str_length(path1)))
		print_error("Error : same texture\n");
}

void	check_texture(t_game *game)
{
	int	i;
	int	j;
	char *list[5];

	i = -1;
	list[0] = game->texture[NO].path;
	list[1] = game->texture[SO].path;
	list[2] = game->texture[WE].path;
	list[3] = game->texture[EA].path;
	list[4] = NULL;
	while (list[++i])
	{
		j = -1;
		while (++j < 4)
		{
			if (i == j)
				continue ;
			else
				check_text_dir(list[i], list[j]);
		}
	}
	check_text_rgb(game);
}

void	set_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		print_error("Error : mlx init\n");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3d");
	if (!game->win)
		print_error("Error : mlx window\n");
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
		print_error("Error : mlx image\n");
	game->img->data = (int *)mlx_get_data_addr(game->img->img, \
	&(game->img->pixel_bits), &(game->img->line_len), &(game->img->endian));
}


int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_av(av[1]))
		print_error("Error : invalid argument\n");
	init_game(&game, av[1]);
	set_game(&game);
	check_map_data(&game);
	if (game.map == NULL)
		print_error("Error : map error\n");
	map_vaildator(&game);
	check_texture(&game);
	init_player(&game);
	init_rgb(&game);
	init_pixel(&game);
	mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, KEY_EXIT, 0, &exit_game, &game);
	do_render(&game);
	mlx_loop(game.mlx);
	return (0);
}
