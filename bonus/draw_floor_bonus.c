/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_floor_bonus.c                                   :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/19 06:04:11 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/20 07:57:50 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <stdio.h>
//START CASTING FLOOR

void	cast_floor(t_info *info)
{
	for(int y = 0; y < info->hght; y++)
	{
      // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = info->dir.x - info->cam.x;
		float rayDirY0 = info->dir.y - info->cam.y;
		float rayDirX1 = info->dir.y + info->cam.x;
		float rayDirY1 = info->dir.y + info->cam.y;
	
      // Current y position compared to the center of the screen (the horizon)
		int p = y - info->hght / 2;

      // Vertical position of the camera.
		float posZ = 0.5 * info->hght;

      // Horizontal distance from the camera to the floor for the current row.
      // 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

      // calculate the real world step vector we have to add for each x (parallel to camera plane)
      // adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / info->wid;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / info->wid;

      // real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->pos.x + rowDistance * rayDirX0;
		float floorY = info->pos.y + rowDistance * rayDirY0;

		for(int x = 0; x < info->wid; ++x)
		{
        	// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);
	
	        // get the texture coordinate from the fractional part
			int tx = (int)(TEX_WID * (floorX - cellX)) & (TEX_WID - 1);
			int ty = (int)(TEX_HGHT * (floorY - cellY)) & (TEX_HGHT - 1);
	
			floorX += floorStepX;
			floorY += floorStepY;
	
	        // choose texture and draw the pixel
			int floorTexture = 5;
			int ceilingTexture = 1;
			unsigned int color;
		
	        // floor
			color = info->texture[floorTexture][TEX_WID * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker

			info->buf[y][x] = color;
	
	        //ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = info->texture[ceilingTexture][TEX_WID * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			info->buf[info->hght - y - 1][x] = color;
		}
	}
}

void	draw_floor1(t_info *info, t_ray *r)
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

void	draw_floor2(t_info *info, t_ray *r, int stripe)
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
		r->pat = ((int)(r->current_floor.x) + (int)(r->current_floor.y)) % 2;
		if (r->pat == 0)
			r->f_tex = 4;
		else
			r->f_tex = 5;
	//floor
		info->buf[y][stripe] = (info->texture[5][TEX_WID * r->floor_tex.y + r->floor_tex.x] >> 1) & 8355711;
//ceiling
		info->buf[info->hght - y][stripe] = info->texture[5][TEX_WID * r->floor_tex.y + r->floor_tex.x];
		y++;
	}
}

