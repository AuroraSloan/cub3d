#include "../includes/cub3d.h"
#include "../libraries/minilibx_mms/mlx.h"

void	draw_image(t_info *info)
{
	int	x;
	int	y;

	y = 0;
	while (y < info->hght)
	{
		x = 0;
		while (x < info->wid)
		{
			info->img.addr[y * info->wid + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}
