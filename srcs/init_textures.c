#include "../includes/cub3d.h"
#include "../libraries/minilibx_mms/mlx.h"
#include "../libraries/libft/libft.h"
#include <stdlib.h>

static void	path_filename_check(t_info *info, char *filename)
{
	int	start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".xpm", 4) != 0)
		free_exit(info, "please use.xpm images");
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

	path_filename_check(info, info->no_path);
	path_filename_check(info, info->so_path);
	path_filename_check(info, info->we_path);
	path_filename_check(info, info->ea_path);
	path_filename_check(info, info->s_path);
	path_filename_check(info, info->f_path);
	path_filename_check(info, "images/sprites/map.xpm");
	path_filename_check(info, "images/sprites/cucco.xpm");
	load_image(info, info->texture[0], info->no_path, &tex);
	load_image(info, info->texture[1], info->so_path, &tex);
	load_image(info, info->texture[2], info->we_path, &tex);
	load_image(info, info->texture[3], info->ea_path, &tex);
	load_image(info, info->texture[4], info->s_path, &tex);
	load_image(info, info->texture[5], info->f_path, &tex);
	load_image(info, info->texture[6], "images/sprites/map.xpm", &tex);
	load_image(info, info->texture[7], "images/sprites/cucco.xpm", &tex);
}

void	init_textures(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 8);
	if (!(info->texture))
		free_exit(info, "Memory allocation error");
	info->texture_flag++;
	while (i < 8)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (TEX_HGHT * TEX_WID));
		if (!(info->texture[i]))
			free_exit(info, "Memory allocaiton error");
		info->texture_flag++;
		i++;
	}
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < TEX_HGHT * TEX_WID)
			info->texture[i][j++] = 0;
		i++;
	}
	load_textures(info);
}
