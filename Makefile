NAME = cub3D

CC = CC
CFLAGS = -Wall -Wextra -Werror

MLX_DIR = ./mlx
MLX = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

GNL_SRC = ./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c

SRCS = main.c

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