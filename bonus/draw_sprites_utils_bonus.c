/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_sprites_utils_bonus.c                           :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/21 22:40:01 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/21 22:40:50 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_sptext_info(t_info *info, int i, int j, int count)
{
	if (info->map[i][j] == 2)
		info->sp_tex[count] = 4;
	else if (info->map[i][j] == 3)
		info->sp_tex[count] = 6;
	else if (info->map[i][j] == 4)
		info->sp_tex[count] = 7;
}
