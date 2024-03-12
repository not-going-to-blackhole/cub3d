#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./mlx/mlx.h"
# include "./get_next_line/get_next_line.h"

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_EXIT 17
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

# define KEY_LEFT 123
# define KEY_RIGHT 124

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define TILE_SIZE 64

# define WALL_HORIZ 0
# define WALL_VERT 1

# define MOV_SPEED 0.05
# define ROT_SPEED 0.05

typedef enum e_dir
{
    NO,
    SO,
    WE,
    EA
}	t_dir;

typedef enum e_arrow
{
    FORWARD,
    BACK,
    LEFT,
    RIGHT
}	t_arrow;

typedef struct s_img
{
    void	*img;
    char    *path;
    int     *data;
    int		pixel_bits;
    int		line_len;
    int		endian;
}	t_img;

typedef struct s_player
{
    double	pos_x;
    double	pos_y;
    double	dir_x;
    double	dir_y;
    double	pln_x;
    double	pln_y;
}	t_player;

typedef struct s_color
{
    int	            c_rgb[3]; //rgb 값 하나씩
    unsigned int    c_bit_rgb; //rgb mlx에 전달하는 24비트 값
    int             c_valid;
    int             f_rgb[3];
    unsigned int    f_bit_rgb;
    int             f_valid;
}	t_color;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    int         file_fd;
    char        *map;
    char        **map_2d;
    int         **pixels;
    int         map_height;
    t_player    *player;
    int         player_cnt;
    t_img       *img;
    t_img       texture[4];
    t_color     *color;
}  t_game;


typedef struct s_render
{
    double      wall_x;
    double      pos;
    double      step;
    int         text_idx;
    int         text_x;
    int         text_y;
    int         color;
}  t_render;

typedef struct s_ray
{
    double    cam_x;
    double    ray_dir_x;
    double    ray_dir_y;
    double    delta_dist_x;
    double    delta_dist_y;
    double    side_dist_x;
    double    side_dist_y;
    double    perp_wall_dist;
    int       hit;
    int       hit_x;
    int       hit_y;
    int       step_x;
    int       step_y;
    int       side;
    int       wall_height;
    int       wall_start;
    int       wall_end;
}	t_ray;

int	key_press(int key, t_game *game);
int	exit_game(t_game *game);
void    do_render(t_game *game);

#endif