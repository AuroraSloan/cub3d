#include "../includes/cub3d.h"
#include "../libraries/minilibx_mms/mlx.h"
#include "../libraries/libft/libft.h"
#include <stdlib.h>

static void	path_filename_check(t_info *info, char *filename)
{
	size_t  start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".xpm", 4) != 0)
		free_exit(info, "please use.xpm images");
}

static void	load_image(t_info *info, int *texture, char *path, t_tex *tex)
{
	int	i;
	int	j;

	i = 0;
    path_filename_check(info, path);
	tex->img = mlx_xpm_file_to_image(info->mlx, path, &tex->wid, &tex->hght);
	if (!(tex->img))
		free_exit(info, "recheck image paths");
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->end);
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

	i = 0;
	info->texture = malloc(sizeof(int *) * 8);
	if (!(info->texture))
		free_exit(info, "Memory allocation error");
	info->texture_flag++;
	while (i < 8)
	{
		info->texture[i] = malloc(sizeof(int) * (TEX_HGHT * TEX_WID));
		if (!(info->texture[i]))
			free_exit(info, "Memory allocaiton error");
        ft_bzero(info->texture[i], sizeof(int) * (TEX_HGHT * TEX_WID));
		info->texture_flag++;
		i++;
	}
	load_textures(info);
}
