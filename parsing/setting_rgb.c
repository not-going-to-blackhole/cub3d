/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeeunpar <yeeunpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:37:41 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 00:18:34 by yeeunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_color(char **tmp_split, int *arr)
{
	int	tmp_str;

	tmp_str = 0;
	while (tmp_split[tmp_str])
		tmp_str++;
	if (tmp_str != 3)
		error("Error\nrgb_color\n");
	tmp_str = 0;
	while (tmp_split[tmp_str])
	{
		arr[tmp_str] = int_atoi(tmp_split[tmp_str]);
		tmp_str++;
	}
}

static void	input_rgb(char *tmp, int *cnt, int *arr, int *check)
{
    int		i;
    int		comma_num;
	char	**comma_split;

	i = 0;
	comma_num = 0;
    comma_split = parsing_str(tmp, ',');
	while (tmp[i])
	{
		if (tmp[i] == ',')
			comma_num++;
		i++;
	}
	if (comma_num >= 3)
		print_error("Error : comma\n");
	checking_rgb_invaild(tmp);
	if (!comma_split)
		print_error("Error : Invaild rgb\n");
	check_color(comma_split, arr);
	(*cnt)++;
	all_free(comma_split);
	*check = 1;
}

static void	checking_rgb_invaild(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		if (!(tmp[i] == ',' || (tmp[i] >= '0' && tmp[i] <= '9') || \
			tmp[i] == '\n'))
			error("Error : Invaild rgb\n");
		i++;
	}
}

void	init_rgb(t_game *game)
{
	game->color->c_bit_rgb = (game->color->c_rgb[0] << 16) | \
		(game->color->c_rgb[1] << 8) | game->color->c_rgb[2];
	game->color->f_bit_rgb = (game->color->f_rgb[0] << 16) | \
		(game->color->f_rgb[1] << 8) | game->color->f_rgb[2];
}

void	setting_rgb(char *line, t_game *game, int *cnt)
{
    int		tmp_str;
	char	**tmp;
	char	*new_line;

	new_line = NULL;
	tmp = parsing_str(line, ' ');
	if (!tmp)
		error("Error : Invaild rgb\n");
	tmp_str = 0;
	while (tmp[tmp_str])
		tmp_str++;
	if (tmp_str == 2)
		new_line = no_new_line(tmp[1]);
	if (!(str_n_compare(tmp[0], "F", counting_str_length(tmp[0]))) \
		&& tmp_str == 2 && game->color->f_valid == 0)
		input_rgb(new_line, cnt, game->color->f_rgb, \
		&(game->color->f_valid));
	else if (!(str_n_compare(tmp[0], "C", counting_str_length(tmp[0]))) \
		&& tmp_str == 2 && game->color->c_valid == 0)
		input_rgb(new_line, cnt, game->color->c_rgb, \
		&(game->color->c_valid));
	else
		error("Error : Invalid rgb\n");
	all_free(tmp);
	free(new_line);
}
