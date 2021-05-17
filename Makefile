NAME = cub3D
LIBS = ./libraries/libft/libft.a ./libraries/libmlx_Linux/libmlx_Linux.a
SRC_DIR = srcs/
SRC_FILES = main.c free_memory.c failed_exit.c create_bmp.c init_game.c \
	init_textures.c parse_cub_info.c parse_line_info.c \
	parse_line_info_utils.c init_map.c init_map_utils.c \
	check_closed_map.c move_player.c hook_utils.c draw_image.c \
	configure_image.c configure_image_utils.c draw_sprites.c \
	sort_sprites.c
B_SRC_DIR = bonus/
B_SRC_FILES = main_bonus.c free_memory_bonus.c failed_exit_bonus.c \
	create_bmp_bonus.c init_game_bonus.c init_textures_bonus.c \
	parse_cub_info_bonus.c parse_line_info_bonus.c init_map_bonus.c \
	parse_line_info_utils_bonus.c init_map_utils_bonus.c draw_image_bonus.c\
	check_closed_map_bonus.c move_player_bonus.c hook_utils_bonus.c \
	configure_image_bonus.c configure_image_utils_bonus.c \
	draw_sprites_bonus.c sort_sprites_bonus.c
SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
B_SRCS = $(addprefix $(B_SRC_DIR), $(B_SRC_FILES))
OBJS = $(SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCS = -I./includes
USR_LIBS = -L/usr/lib -lXext -lm -lX11

$(NAME):$(OBJS)
	make -C libraries/libft
	make -C libraries/libmlx_Linux
	$(CC) -o $(NAME) $(OBJS) $(LIBS) $(USR_LIBS) $(INCS)

all:$(NAME)

bonus: $(B_OBJS)
	make -C libraries/libft
	make -C libraries/libmlx_Linux
	$(CC) -o $(NAME) $(B_OBJS) $(LIBS) $(USR_LIBS) $(INCS)

clean:
	rm -f $(OBJS)
	rm -f $(B_OBJS)
	make clean -C libraries/libft
	make clean -C libraries/libmlx_Linux

fclean: clean
	rm -f $(NAME)
	make fclean -C libraries/libft

re: fclean all

.PHONY: all clean fclean re
