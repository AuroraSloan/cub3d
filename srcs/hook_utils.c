/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  hook_utils.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 14:59:56 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/15 15:17:55 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

int	successful_exit(t_info *info)
{
	free_memory(info);
	if (info->bmp == 1)
		printf("The image cub3D.bmp was successfully created\n");
	else
		printf("See you next time!\n");
	exit(EXIT_SUCCESS);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == ESC)
		successful_exit(info);
	else if (keycode == LFT)
		info->key.left = 1;
	else if (keycode == RT)
		info->key.right = 1;
	else if (keycode == W)
		info->key.w = 1;
	else if (keycode == A)
		info->key.a = 1;
	else if (keycode == S)
		info->key.s = 1;
	else if (keycode == D)
		info->key.d = 1;
	return (0);
}

int	key_release(int keycode, t_info *info)
{
	if (keycode == ESC)
		successful_exit(info);
	else if (keycode == LFT)
		info->key.left = 0;
	else if (keycode == RT)
		info->key.right = 0;
	else if (keycode == W)
		info->key.w = 0;
	else if (keycode == A)
		info->key.a = 0;
	else if (keycode == S)
		info->key.s = 0;
	else if (keycode == D)
		info->key.d = 0;
	return (0);
}
