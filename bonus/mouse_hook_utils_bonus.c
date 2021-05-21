/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  mouse_hook_utils_bonus.c                             :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/19 05:13:47 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/20 16:34:57 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	mouse_movement(int x, int y, t_info *info)
{	
	if (info->mouse.x == -1)
	{
		info->mouse.x = x;
		info->old_mouse.x = x;
		info->mouse.y = y;
		info->old_mouse.y = y;
	}
	else
	{
		info->old_mouse.x = info->mouse.x;
		info->mouse.x = x;
		info->old_mouse.y = info->mouse.y;
		info->mouse.y = y;
	}
	if ((info->mouse.x < (info->wid / 2) && info->mouse.x < info->old_mouse.x))
		turn_left(info);
	if ((info->mouse.x > (info->wid / 2) && info->mouse.x > info->old_mouse.x))
		turn_right(info);
	return (0);
}

int	mouse_enter(t_info *info)
{
	info->exit = 0;
	return (0);
}

int	mouse_exit(t_info *info)
{
	info->exit = 1;
	return (0);
}
