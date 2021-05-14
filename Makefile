NAME = cub3D
LIBS = ./libraries/libft/libft.a ./libraries/libmlx_Linux/libmlx_Linux.a
SRC_DIR = srcs/
SRC_FILES = main.c free_memory.c failed_exit.c create_bmp.c init_game.c \
	init_textures.c parse_cub_info.c parse_line_info.c \
	parse_line_info_utils.c init_map.c init_map_utils.c \
	check_closed_map.c move_player.c hook_utils.c draw_image.c \
	configure_image.c configure_image_utils.c draw_sprites.c \
	sort_sprites.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes
USR_LIBS = -L/usr/lib -lXext -lm -lX11

all:$(NAME)

$(NAME):$(OBJS)
	make -C libraries/libft
	make -C libraries/libmlx_Linux
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS) 

clean:
	rm -f $(OBJS)
	make clean -C libraries/libft
	make clean -C libraries/libmlx_Linux

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re
