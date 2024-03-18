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

# define SUCCESS 0
# define FAIL 1

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

//hooks.c
int	    key_press(int key, t_game *game);
int	    exit_game(t_game *game);

//move.c
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_forward(t_game *game);
void	move_back(t_game *game);

//render.c
void    do_render(t_game *game);

//init_ray.c
void    init_ray(t_game *game, t_ray *ray, int x);

//raycasting.c
void    perform_ray(t_game *game, t_ray *ray);
void    calc_wall(t_game *game, t_ray *ray);
void    set_texture(t_game *game, t_ray *ray, t_render *render);
void    paint_wall(t_game *game, t_ray *ray, t_render *render, int x);

// map_validator.c
void	map_vaildator(t_game *game);

// map_validator2.c
void	checking_map2(char **map);

//parse_map_and_read.c
void	parse_map_and_read(t_game *game);
int	    line_counting(char *line);

//str.c
int	    set_atoi(char *str);
int	    str_ncompare(const char *str1, const char *str2, size_t n);
int	    counting_str_length(char const *str);
long	check_atoi(char *str);

//strstr.c
char	*duplicate_string(const char *str);
char	*remove_new_line(char *line);

//free.c
void	print_error(const char *tmp);
char	**all_free(char **word);

//parsing_str.c
char	**parsing_str(char const *str1, char str2);

//wall_vaildator.c
void	checking_wall(char **map);
int	    check_all_spaces(char *map);

//setting_rgb.c
void	init_rgb(t_game *game);
void	setting_rgb(char *line, t_game *game, int *cnt);

//check_map_data.c
int	    cnting_line_str(char *line);
void	check_map_data(t_game *game);

//check_direction.c
void	check_direction(char *line, t_game *game, int *cnt);

#endif