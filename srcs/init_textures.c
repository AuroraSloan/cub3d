/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  init_textures.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/13 21:38:49 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/14 20:39:27 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../libraries/libmlx_Linux/mlx.h"
#include "../libraries/libft/libft.h"
#include <stdlib.h>

static int	path_filename_check(char *filename)
{
	int	start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".xpm", 4) != 0)
		return (-1);
	return (1);
}

static void	load_image(t_info *info, int *texture, char *path, t_tex *tex)
{
	int	i;
	int	j;

	i = 0;
	tex->img = mlx_xpm_file_to_image(info->mlx, path, &tex->wid, &tex->hght);
	if (!(tex->img))
		free_exit(info, "recheck image paths");
	tex->addr = (int *)
		mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->end);
	while (i < tex->hght)
	{
		j = 0;
		while (j < tex->wid)
		{
			texture[tex->wid * i + j] = tex->addr[tex->wid * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(info->mlx, tex->img);
}

static void	load_textures(t_info *info)
{
	t_tex	tex;
	int		check;

	check = path_filename_check(info->no_path);
	if (check == -1)
		free_exit(info, "please use .xpm images");
	check = path_filename_check(info->so_path);
	if (check == -1)
		free_exit(info, "please use .xpm images");
	check = path_filename_check(info->we_path);
	if (check == -1)
		free_exit(info, "please use .xpm images");
	check = path_filename_check(info->ea_path);
	if (check == -1)
		free_exit(info, "please use .xpm images");
	check = path_filename_check(info->s_path);
	if (check == -1)
		free_exit(info, "please use .xpm images");
	load_image(info, info->texture[0], info->no_path, &tex);
	load_image(info, info->texture[1], info->so_path, &tex);
	load_image(info, info->texture[2], info->we_path, &tex);
	load_image(info, info->texture[3], info->ea_path, &tex);
	load_image(info, info->texture[4], info->s_path, &tex);
}

void	init_textures(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 5);
	if (!(info->texture))
		free_exit(info, "Memory allocation error");
	info->texture_flag++;
	while (i < 5)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (TEX_HGHT * TEX_WID));
		if (!(info->texture[i]))
			free_exit(info, "Memory allocaiton error");
		info->texture_flag++;
		i++;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < TEX_HGHT * TEX_WID)
			info->texture[i][j++] = 0;
		i++;
	}
	load_textures(info);
}
