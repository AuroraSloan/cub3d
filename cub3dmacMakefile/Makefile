NAME = cub3d
LIBS = ./libraries/libft/libft.a libmlx.dylib #./libraries/libmlx_Linux/libmlx_Linux.a
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
USR_LIBS = -lmlx -framework OpenGL -framework AppKit #-L/usr/lib -lXext -lX11 -lm

$(NAME): $(OBJS) includes/cub3d.h
	make -C libraries/libft
#	make -C libraries/libmlx_Linux
	make -C libraries/minilibx_mms
	cp libraries/minilibx_mms/libmlx.dylib ./
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm libmlx.dylib
	make clean -C libraries/libft
#	make clean -C libraries/libmlx_Linux
	make clean -C libraries/minilibx_mms

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re
