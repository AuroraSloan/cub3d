/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_floor_bonus.c                                   :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/19 06:04:11 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/19 07:06:51 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

//START CASTING FLOOR
void	init_floor_casting(t_info *info, t_ray *r)
{
	if (r->side == 0 && r->dir.x > 0)
	{
		r->floor_wall.x = r->map.x;
		r->floor_wall.y = r->map.y + info->wall_x;
	}
	else if (r->side == 0 && r->dir.x < 0)
	{
		r->floor_wall.x = r->map.x + 1.0;
		r->floor_wall.y = r->map.y + info->wall_x;
	}
	else if (r->side == 1 && r->dir.x > 0)
	{
		r->floor_wall.x = r->map.x + info->wall_x;
		r->floor_wall.y = r->map.y; 
	}
	else
	{
		r->floor_wall.x = r->map.x + info->wall_x;
		r->floor_wall.y = r->map.y + 1.0; 
	}
	r->dist_wall = r->dist;
	r->dist_player = 0.0;	
}

void	draw_floor(t_info *info, t_ray *r, int stripe)
{
	int	y;

	if (r->draw_end < 0)
		r->draw_end = info->hght;
	y = r->draw_end + 1;
	while (y < info->hght)
	{
		r->current_dist = info->hght / (2.0 * y - info->hght);
		r->weight = (r->current_dist - r->dist_player) / (r->dist_wall - r->dist_player);
		r->current_floor.x = r->weight * r->floor_wall.x + (1.0 - r->weight) * info->pos.x;
		r->current_floor.y = r->weight * r->floor_wall.y + (1.0 - r->weight) * info->pos.y;
		r->floor_tex.x = (int)(r->current_floor.x * TEX_WID) % TEX_WID;
		r->floor_tex.y = (int)(r->current_floor.y * TEX_HGHT) % TEX_HGHT;
		r->pat = ((int)(r->current_floor.x) + (int)(r->current_floor.y)) & 2;
		if (r->pat == 0)
			r->f_tex = 5;
		else
			r->f_tex = 5;
	//floor
		info->buf[y][stripe] = (info->texture[r->f_tex][TEX_WID * r->floor_tex.y + r->floor_tex.x] >> 1) & 8355711;
//ceiling
//info->buf[info->hght - y][x] = info->texture[4][TEX_WID * r.floor_tex.y + r.floor_tex.x];
		y++;
	}
}
