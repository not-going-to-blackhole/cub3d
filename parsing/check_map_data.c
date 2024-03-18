/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 23:53:18 by yeeunpar          #+#    #+#             */
/*   Updated: 2024/03/19 03:06:24 by woorikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	checking_line(char *line, int line_len, t_game *game)
{
	int	i;

	i = -1;
	while (++i < line_len)
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' \
			|| line[i] == '\n')
			continue ;
		else if (line[i] == 'N' || line[i] == 'S' || \
			line[i] == 'W' || line[i] == 'E')
			game->player_cnt++;
		else
			return (0);
	}
	return (1);
}

static void	check_dir_rgb(char *line, t_game *game, int *cnt)
{
	char	**tmp;

	tmp = parsing_str(line, ' ');
	printf("start check_dir_rgb\n");
	printf("tmp[0] : %s\ntmp[1]: %s\n", tmp[0], tmp[1]);
	if (tmp == (void *)0 || tmp[0] == (void *)0)
		print_error("Error: Failed to split dir or rgb string\n");
	if (line[0] == '\n' && !(line[1]))
	{
		all_free(tmp);
		return ;
	}
	else if (!(str_ncompare(tmp[0], "F", 1)) || \
		!(str_ncompare(tmp[0], "C", 1)))
		setting_rgb(line, game, cnt);
	else if (!(str_ncompare(tmp[0], "NO", 2)) || \
		!(str_ncompare(tmp[0], "SO", 2)) || \
		!(str_ncompare(tmp[0], "WE", 2)) || \
		!(str_ncompare(tmp[0], "EA", 2)))
		check_direction(line, game, cnt);
	else
		print_error("Error : Invalid dir or rgb\n");
	all_free(tmp);
	printf("check_dir_rgb\n");
}

static int	checking_map(char **line, char **map_buf, t_game *game)
{
	if (checking_line(*line, counting_str_length(*line), game) == 1)
	{
		*map_buf = ft_strjoin_gnl(*map_buf, *line);
		return (0);
	}
	else
	{
		free(*map_buf);
		free(*line);
		*map_buf = NULL;
		*line = NULL;
		return (1);
	}
}

int	cnting_line_str(char *line)
{
	int	i;

	i = 0;
    if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		i++;
	}
	return (i);
}

void	check_map_data(t_game *game)
{
    int		cnt;
	char	*map_buf;
	char	*line;

    cnt = 0;
	map_buf = NULL;
	line = NULL;
	printf("check_map_data start\n");
	printf("game->file_fd : %d\n", game->file_fd);
	while (42)
	{
		line = get_next_line(game->file_fd);
		printf("line : %s\n", line);
		if (!line)
			break ;
		printf("cnt : %d\n", cnt);
		if (cnt <= 5)
		{
			check_dir_rgb(line, game, &cnt);
			printf("after check_dir_rgb\n");
		}
		else
			if (checking_map(&line, &map_buf, game) == 1)
				print_error("Error : Invalid input map\n");
		free(line);
		line = NULL;
	}
	close(game->file_fd);
	game->map = map_buf;
	free(line);
	printf("check_map_data\n");
}
