/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  configure_image_utils_bonus.c                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:22:02 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/19 06:42:34 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <math.h>

void	select_texture(t_info *info, t_ray *r)
{
	if (r->side == 0 && r->step.x < 0)
		info->tex_num = 0;
	else if (r->side == 0 && r->step.x > 0)
		info->tex_num = 1;
	else if (r->side == 1 && r->step.y < 0)
		info->tex_num = 2;
	else if (r->side == 1 && r->step.y > 0)
		info->tex_num = 3;
}

void	init_ray_information(t_info *info, t_ray *r, int stripe)
{
	r->cam_x = 2 * stripe / (double)info->wid - 1;
	r->dir.x = info->dir.x + info->cam.x * r->cam_x;
	r->dir.y = info->dir.y + info->cam.y * r->cam_x;
	r->map.x = (int)info->pos.x;
	r->map.y = (int)info->pos.y;
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	r->hit = 0;
}

void	calculate_ray_distance(t_info *info, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (info->map[(int)r->map.x][(int)r->map.y] == 1)
			r->hit = 1;
	}
	if (r->side == 0)
		r->dist = (r->map.x - info->pos.x
				+ (1 - r->step.x) / 2) / r->dir.x;
	else
		r->dist = (r->map.y - info->pos.y
				+ (1 - r->step.y) / 2) / r->dir.y;
}
