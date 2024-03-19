/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:14:20 by woorikim          #+#    #+#             */
/*   Updated: 2024/03/19 16:42:52 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_text_rgb(t_game *game)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (game->color->c_rgb[i] != game->color->f_rgb[i])
			return ;
		i++;
	}
	print_error("Error\nSame color\n");
}

static void	check_text_dir(char *path1, char *path2)
{
	if (!str_ncompare(path1, path2, counting_str_length(path1)))
		print_error("Error\nSame texture\n");
}

void	check_texture(t_game *game)
{
	int		i;
	int		j;
	char	*list[5];

	i = -1;
	list[0] = game->texture[NO].path;
	list[1] = game->texture[SO].path;
	list[2] = game->texture[WE].path;
	list[3] = game->texture[EA].path;
	list[4] = NULL;
	while (++i < 4)
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
