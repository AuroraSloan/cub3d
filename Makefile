UNAME := $(shell uname)

NAME = cub3d
SRC_DIR = srcs/
SRC_FILES = main.c free_memory.c failed_exit.c create_bmp.c init_game.c \
	init_textures.c parse_cub_info.c parse_line_info.c init_map.c \
	parse_line_info_utils.c init_map_utils.c draw_image.c draw_floor.c \
	check_closed_map.c move_player.c hook_utils.c  configure_image.c \
	configure_image_utils.c draw_sprites.c sort_sprites.c mouse_hook_utils.c \
	draw_sprites_utils.c draw_mini_map.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes
HEADER = includes/*

LINUX_MLX = minilibx-linux
LINUX_MLX_SRC = https://github.com/42Paris/minilibx-linux.git

MAC_MLX = minilibx_mms

ifeq ($(UNAME), Linux)
LIBS = ./libraries/libft/libft.a ./libraries/minilibx-linux/libmlx_Linux.a
USR_LIBS = -L/usr/lib -lXext -lm -lX11
all: linux_mlx $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C libraries/libft
	make -C libraries/minilibx-linux
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

linux_mlx:
	@if [ ! -d libraries/"$(LINUX_MLX)" ]; then \
		git clone $(LINUX_MLX_SRC) libraries/$(LINUX_MLX); \
	fi; \

clean:
	rm -f $(OBJS)
	make clean -C libraries/libft
	make clean -C libraries/$(LINUX_MLX)

else
LIBS = ./libraries/libft/libft.a ./libraries/minilibx_mms/libmlx.a
USR_LIBS = -framework OpenGL -framework AppKit
all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	make -C libraries/libft
	make -C libraries/$(MAC_MLX)
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

clean:
	rm -f $(OBJS)
	make clean -C libraries/libft
	make clean -C libraries/$(MAC_MLX)

endif

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re linux_mlx