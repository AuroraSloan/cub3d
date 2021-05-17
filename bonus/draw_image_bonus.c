/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_image_bonus.c                                   :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:12:42 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:16:15 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../libraries/libmlx_Linux/mlx.h"

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
