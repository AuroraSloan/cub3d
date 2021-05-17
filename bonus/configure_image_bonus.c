/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  configure_image_bonus.c                              :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:15:16 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:15:19 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <math.h>

static void	set_ray_distance(t_info *info, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (info->pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - info->pos.x) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (info->pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - info->pos.y) * r->delta_dist.y;
	}
	calculate_ray_distance(info, r);
}

static void	calculate_wall_height(t_info *info, t_ray *r)
{
	r->wall_hight = (int)(info->hght / r->dist);
	r->draw_start = -r->wall_hight / 2 + info->hght / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->wall_hight / 2 + info->hght / 2;
	if (r->draw_end >= info->hght || r->draw_end < 0)
		r->draw_end = info->hght - 1;
}

void	calculate_texture_stripe(t_info *info, t_ray *r)
{
	if (r->side == 0)
		info->wall_x = info->pos.y + r->dist * r->dir.y;
	else
		info->wall_x = info->pos.x + r->dist * r->dir.x;
	info->wall_x -= floor(info->wall_x);
	info->tex.x = (int)(info->wall_x * (double)TEX_WID);
	if (r->side == 0 && r->dir.x > 0)
		info->tex.x = TEX_WID - info->tex.x - 1;
	if (r->side == 1 && r->dir.y < 0)
		info->tex.x = TEX_WID - info->tex.x - 1;
	info->step_y = 1.0 * TEX_HGHT / r->wall_hight;
	info->tex_pos = (r->draw_start - info->hght / 2 + r->wall_hight / 2)
		* info->step_y;
}

static void	draw_buffer(t_info *info, t_ray r, int stripe)
{
	int	sky;
	int	floor;
	int	wall;
	int	pixel;

	sky = 0;
	while (sky < r.draw_start)
		info->buf[sky++][stripe] = info->c_color;
	wall = r.draw_start;
	while (wall < r.draw_end)
	{
		info->tex.y = (int)info->tex_pos & (TEX_HGHT - 1);
		info->tex_pos += info->step_y;
		pixel = info->texture[info->tex_num][TEX_HGHT
			* info->tex.y + info->tex.x];
		info->buf[wall][stripe] = pixel;
		wall++;
	}
	floor = r.draw_end;
	while (floor < info->hght)
		info->buf[floor++][stripe] = info->f_color;
}

void	configure_image(t_info *info)
{
	t_ray	r;
	int		stripe;

	stripe = 0;
	while (stripe < info->wid)
	{
		init_ray_information(info, &r, stripe);
		set_ray_distance(info, &r);
		calculate_wall_height(info, &r);
		select_texture(info, &r);
		calculate_texture_stripe(info, &r);
		draw_buffer(info, r, stripe);
		info->sp_buf[stripe] = r.dist;
		stripe++;
	}
	if (info->sp_count > 0)
		draw_sprites(info);
}
