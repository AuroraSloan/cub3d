#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include "../libraries/minilibx_mms/mlx.h"
#include <fcntl.h>
#include <unistd.h>

static void	filename_check(t_info *info, char *filename)
{
	size_t  start;
	int		fd;
	char	*buf;
	ssize_t  ret;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".cub", 4) != 0)
		ft_failed_exit("The second argument should be a .cub file", NULL);
	info->name = filename;
    fd = open(filename, O_RDONLY);
    check_failed_fd(info, fd);
	buf = malloc(10);
    if (!buf)
        ft_failed_exit("memory error", NULL);
    ret = read(fd, buf, 10);
    safe_free(buf);
    close(fd);
	if (ret == -1)
		ft_failed_exit("Check .cub file is correct type of file", NULL);
}

static int	game_loop(t_info *info)
{
	char	*number;

	move_player(info);
	configure_image(info);
	draw_image(info);
	number = ft_itoa(info->cucco);
	mlx_string_put(info->mlx, info->win, info->wid - 120, 30,
		0X00000000, "cucco count");
	mlx_string_put(info->mlx, info->win, info->wid - 30, 30,
		0X00000000, number);
	ft_free(number);
    if (info->cucco == MABE_CUCCO_COUNT)
        successful_exit(info);
	number = NULL;
	return (0);
}

static void	init_game(t_info *info)
{
	init_pointers_keys(info);
	info->mlx = mlx_init();
	if (!(info->mlx))
		free_exit(info, "Connection to X-server Failed");
	info->mv_spd = .06;
	info->rot_spd = .03;
	info->map_flag = -1;
	info->buf_flag = -1;
	info->texture_flag = -1;
	info->c_color = -1;
	info->wid = 0;
	info->hght = 0;
	info->row_count = 0;
	info->col_count = 0;
	info->bmp = 0;
	info->mini_map = 0;
	info->cucco = 0;
	count_map_rows(info);
	parse_cub_info(info);
	init_buf(info);
	init_textures(info);
	init_sprite_info(info);
	info->mouse.x = -1;
	info->old_mouse.x = -1;
	info->exit = 0;
}

static void	check_args(t_info *info, int argc, char **argv)
{
	info->save = 0;
	if (argc > 3)
		ft_failed_exit("Too many arguments", NULL);
	else if (argc < 2)
		ft_failed_exit("Please select which .cub file to read", NULL);
	else if (argc == 3 && (ft_memcmp("--save", argv[2], 6) != 0))
		ft_failed_exit("Second argument should be --save", NULL);
	if (argc == 3 && (ft_memcmp("--save", argv[2], 6) == 0))
		info->save = 1;
}

int	main(int argc, char **argv)
{
	t_info	info;

	check_args(&info, argc, argv);
	filename_check(&info, argv[1]);
	init_game(&info);
	if (argc == 3 && (ft_memcmp("--save", argv[2], 6) == 0))
		create_bmp(&info, "cub3D.bmp");
	info.win = mlx_new_window(info.mlx, info.wid, info.hght, "Cub3D");
	if (!(info.win))
		free_exit(&info, "Could not create window");
	info.img.img = mlx_new_image(info.mlx, info.wid, info.hght);
	if (!(info.img.img))
		free_exit(&info, "Could not create image");
	info.img.addr = (int *)mlx_get_data_addr(info.img.img,
			&info.img.bpp, &info.img.len, &info.img.end);
	mlx_loop_hook(info.mlx, game_loop, &info);
	mlx_hook(info.win, 2, 1L << 0, &key_press, &info);
	mlx_hook(info.win, 3, 1L << 1, &key_release, &info);
	mlx_hook(info.win, 6, 1L << 6, &mouse_movement, &info);
	mlx_hook(info.win, 7, 1L << 4, &mouse_enter, &info);
	mlx_hook(info.win, 8, 1L << 5, &mouse_exit, &info);
	mlx_hook(info.win, 17, 1L << 17, &successful_exit, &info);
	mlx_loop(info.mlx);
}
