NAME = cub3D
LIBS = ./libraries/libft/libft.a ./libraries/libmlx_Linux/libmlx_Linux.a
SRC_DIR = srcs/
SRC_FILES = main.c
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
