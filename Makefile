# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: woorikim <woorikim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:32:33 by woorikim          #+#    #+#              #
#    Updated: 2024/03/19 16:47:23 by woorikim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
MLX = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

GNL_SRC = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

SRCS = main.c \
	executing/hooks.c executing/move.c executing/render.c \
	executing/init_ray.c executing/raycasting.c executing/init_game.c \
	parsing/map_validator.c parsing/map_validator2.c parsing/parse_map_and_read.c \
	parsing/str.c parsing/strstr.c parsing/free.c parsing/parsing_str.c \
	parsing/wall_vaildator.c parsing/setting_rgb.c parsing/check_map_data.c \
	parsing/check_direction.c parsing/check_text.c

ObJS = $(SRCS:.c=.o) $(GNL_SRC:.c=.o)

all: $(NAME)

$(NAME): $(ObJS)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(ObJS) $(MLX)

clean:
	@make clean -C $(MLX_DIR)
	@rm -f $(ObJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re