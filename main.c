/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:23:33 by woorikim          #+#    #+#             */
/*   Updated: 2024/03/19 16:41:49 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_av(char *av)
{
	int		str;
	int		tmp_cnt;
	char	**tmp;

	tmp_cnt = 0;
	tmp = parsing_str(av, '/');
	if (!tmp)
		print_error("Error\nsplit argv\n");
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

void	set_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		print_error("Error\nmlx init\n");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!game->win)
		print_error("Error\nmlx window\n");
	game->img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->img->img)
		print_error("Error\nmlx image\n");
	game->img->data = (int *)mlx_get_data_addr(game->img->img, \
	&(game->img->pixel_bits), &(game->img->line_len), &(game->img->endian));
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || check_av(av[1]))
		print_error("Error\nInvalid argument\n");
	init_game(&game, av[1]);
	set_game(&game);
	init_pixel(&game);
	check_map_data(&game);
	if (game.map == NULL)
		print_error("Error\nMap error\n");
	map_validator(&game);
	check_texture(&game);
	init_player(&game);
	init_rgb(&game);
	mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, KEY_EXIT, 0, &exit_game, &game);
	do_render(&game);
	mlx_loop(game.mlx);
	return (0);
}
