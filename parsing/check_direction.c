#include "../cub3d.h"

static void	put_mlx_image(t_game *game, char *path, t_img *img)
{
	int	width;
	int	height;

	img->img = NULL;
	img->img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (!img->img)
		print_error("Error : Impossible put mlx image\n");
	img->data = (int *)mlx_get_data_addr(img->img, &(img->pixel_bits), \
		&(img->line_len), &(img->endian));
	if (!img->data)
		print_error("Error : Impossible put mlx image\n");
}

static void	input_img(int *cnt, t_game *game, char *tmp, int flag)
{
	char	*tmp_copy;

	tmp_copy = duplicate_string(tmp);
	if (flag == NO)
	{
		put_mlx_image(game, tmp, &(game->texture[NO]));
		game->texture[NO].path = tmp_copy;
	}
	else if (flag == SO)
	{
		put_mlx_image(game, tmp, &(game->texture[SO]));
		game->texture[SO].path = tmp_copy;
	}
	else if (flag == EA)
	{
		put_mlx_image(game, tmp, &(game->texture[EA]));
		game->texture[EA].path = tmp_copy;
	}
	else if (flag == WE)
	{
		put_mlx_image(game, tmp, &(game->texture[WE]));
		game->texture[WE].path = tmp_copy;
	}
	(*cnt)++;
}

void	choice_direction(int	*cnt, t_game *game, char *new_line, char *tmp)
{
	if (!(str_ncompare(tmp, "NO", counting_str_length(tmp))) && \
		!(game->texture[NO].path))
		input_img(cnt, game, new_line, NO);
	else if (!(str_ncompare(tmp, "SO", counting_str_length(tmp))) \
		&& !(game->texture[SO].path))
		input_img(cnt, game, new_line, SO);
	else if (!(str_ncompare(tmp, "WE", counting_str_length(tmp))) \
		&& !(game->texture[WE].path))
		input_img(cnt, game, new_line, WE);
	else if (!(str_ncompare(tmp, "EA", counting_str_length(tmp))) \
		&& !(game->texture[EA].path))
		input_img(cnt, game, new_line, EA);
	else
		print_error("Error : Invaild direction\n");
}

static void	check_extension_error(char *file)
{
	int	len;

	len = counting_str_length(file);
	if (len <= 4)
		print_error("Error : Impossible extension\n");
	if (!(file[len - 1] == 'm' && file[len - 2] == 'p' \
		&& file[len - 3] == 'x' && file[len - 4] == '.'))
		print_error("Error : Impossible extension\n");
}

void	check_direction(char *line, t_game *game, int *cnt)
{
    int		tmp_str;
	char	**tmp;
	char	*new_line;

    tmp_str = 0;
	new_line = NULL;
	tmp = parsing_str(line, ' ');
	if (!tmp)
		print_error("Error\ndirection\n");
	while (tmp[tmp_str])
		tmp_str++;
	if (tmp_str == 2)
	{
		new_line = remove_new_line(tmp[1]);
		check_extension_error(new_line);
	}
	if (tmp_str == 2)
		choice_direction(cnt, game, new_line, tmp[0]);
	else
		print_error("Error : Invaild direction\n");
	all_free(tmp);
	free(new_line);
}