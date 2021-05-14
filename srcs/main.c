/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  main.c                                               :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompso <jthomps@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:21 by jthompso          #+#    #+#             */
/*  Updated: 2021/05/14 15:48:51 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include "../libraries/libmlx_Linux/mlx.h"

void	filename_check(t_info *info, char *filename)
{
	int	start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".cub", 4) != 0)
		failed_exit("The second argument should be a .cub file");
	info->name = filename;
}

int	game_loop(t_info *info)
{
	move_player(info);
	configure_image(info);
	draw_image(info);
	return (0);
}

void	init_game(t_info *info)
{
	init_pointers_keys(info);
	info->mlx = mlx_init();
	if (!(info->mlx))
		free_exit(info, "Connection to X-server Failed");
	info->mv_spd = .03;
	info->rot_spd = .03;
	info->map_flag = -1;
	info->buf_flag = -1;
	info->texture_flag = -1;
	info->f_color = -1;
	info->c_color = -1;
	info->wid = 0;
	info->hght = 0;
	info->row_count = 0;
	info->col_count = 0;
	count_map_rows(info);
	parse_cub_info(info);
	init_buf(info);
	init_textures(info);
	init_sprite_info(info);
}

void	check_arg_count(int argc, char **argv)
{
	if (argc > 3)
		failed_exit("Too many arguments");
	else if (argc < 2)
		failed_exit("Please select which .cub file to read");
	else if (argc == 3 && (ft_memcmp("--save", argv[2], 6) != 0))
		failed_exit("Second argument should be --save");
}

int	main(int argc, char **argv)
{
	t_info	info;

	check_arg_count(argc, argv);
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
	mlx_hook(info.win, 33, 1L << 17, &successful_exit, &info);
	mlx_loop(info.mlx);
}	
