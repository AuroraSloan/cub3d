#include "../includes/cub3d.h"

int	is_start(char start)
{
	return (start == 'N' || start == 'S' || start == 'E' || start == 'W');
}

void	init_n_s_vectors(t_info *info)
{
	if (info->start == 'N')
	{
		info->dir.x = -1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = 0.66;
	}
	else if (info->start == 'S')
	{
		info->dir.x = 1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = -0.66;
	}
}

void	init_w_e_vectors(t_info *info)
{
	if (info->start == 'E')
	{
		info->dir.x = 0.0;
		info->dir.y = 1.0;
		info->cam.x = 0.66;
		info->cam.y = 0.0;
	}
	else if (info->start == 'W')
	{
		info->dir.x = 0.0;
		info->dir.y = -1.0;
		info->cam.x = -.66;
		info->cam.y = 0.0;
	}
}
