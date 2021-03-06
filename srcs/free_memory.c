#include "../includes/cub3d.h"
#include "../libraries/minilibx_mms/mlx.h"
#include <stdlib.h>

void	safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

static void	free_paths(t_info *info)
{
	if (info->no_path != NULL)
		safe_free(info->no_path);
	if (info->so_path != NULL)
		safe_free(info->so_path);
	if (info->we_path != NULL)
		safe_free(info->we_path);
	if (info->ea_path != NULL)
		safe_free(info->ea_path);
	if (info->s_path != NULL)
		safe_free(info->s_path);
	if (info->f_path != NULL)
		safe_free(info->f_path);
}

static void	free_matrices(t_info *info)
{
	int	i;

	i = 0;
	if (info->map_flag >= 0)
	{
		while (i < info->map_flag)
			safe_free(info->map[i++]);
		safe_free(info->map);
	}
	i = 0;
	if (info->texture_flag >= 0)
	{
		while (i < info->texture_flag)
			safe_free(info->texture[i++]);
		safe_free(info->texture);
	}
	i = 0;
	if (info->buf_flag >= 0)
	{
		while (i < info->buf_flag)
			safe_free(info->buf[i++]);
		safe_free(info->buf);
	}
}

void	free_memory(t_info *info)
{
	free_paths(info);
	free_matrices(info);
	if (info->sp_buf != NULL)
		safe_free(info->sp_buf);
	if (info->sp_dist != NULL)
		safe_free(info->sp_dist);
	if (info->sp_ordr != NULL)
		safe_free(info->sp_ordr);
	if (info->sprt != NULL)
		safe_free(info->sprt);
	if (info->sp_tex != NULL)
		safe_free(info->sp_tex);
	if (info->img.img != NULL)
		mlx_destroy_image(info->mlx, info->img.img);
	if (info->win != NULL)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx != NULL)
    {
        # ifdef __linux__
        mlx_destroy_display(info->mlx);
        mlx_loop_end(info->mlx);
        # endif
        safe_free(info->mlx);
    }
}
