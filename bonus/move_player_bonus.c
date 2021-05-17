/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  move_player_bonus.c                                  :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 14:54:34 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:18:21 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <math.h>

static void	turn_left(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(info->rot_spd)
		- info->dir.y * sin(info->rot_spd);
	info->dir.y = old_dir * sin(info->rot_spd)
		+ info->dir.y * cos(info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(info->rot_spd)
		- info->cam.y * sin(info->rot_spd);
	info->cam.y = old_cam * sin(info->rot_spd)
		+ info->cam.y * cos(info->rot_spd);
}

static void	turn_right(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(-info->rot_spd)
		- info->dir.y * sin(-info->rot_spd);
	info->dir.y = old_dir * sin(-info->rot_spd)
		+ info->dir.y * cos(-info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(-info->rot_spd)
		- info->cam.y * sin(-info->rot_spd);
	info->cam.y = old_cam * sin(-info->rot_spd)
		+ info->cam.y * cos(-info->rot_spd);
}

static void	move_left_right(t_info *info)
{
	if (info->key.a)
	{
		if (!info->map[(int)(info->pos.x
				- info->cam.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				- info->cam.y * info->mv_spd)])
			info->pos.y -= info->cam.y * info->mv_spd;
	}
	if (info->key.d)
	{
		if (!info->map[(int)(info->pos.x
				+ info->cam.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				+ info->cam.y * info->mv_spd)])
			info->pos.y += info->cam.y * info->mv_spd;
	}
}

static void	move_forwrd_backwrd(t_info *info)
{
	if (info->key.w)
	{
		if (!info->map[(int)(info->pos.x
				+ info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				+ info->dir.y * info->mv_spd)])
			info->pos.y += info->dir.y * info->mv_spd;
	}
	if (info->key.s)
	{
		if (!info->map[(int)(info->pos.x
				- info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				- info->dir.y * info->mv_spd)])
			info->pos.y -= info->dir.y * info->mv_spd;
	}
}

void	move_player(t_info *info)
{
	if (info->key.left)
		turn_left(info);
	if (info->key.right)
		turn_right(info);
	move_left_right(info);
	move_forwrd_backwrd(info);
}
