/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_mini_map.c                                      :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/22 02:38:35 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/22 03:27:14 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_mm_buf(t_info *info, t_mini_map *mm, int color)
{
	while (mm->wid_cnt < mm->mm_wid / info->col_count)
	{
		info->buf[mm->mm_i][mm->mm_j++] = color;
		mm->wid_cnt++;
	}
}

static void	draw_items(t_info *info, t_mini_map *mm)
{
	if (info->map[mm->map_i][mm->map_j] == 1)
		draw_mm_buf(info, mm, 0X00FFFFFF);
	else if (mm->map_i == (int)info->pos.x && mm->map_j == (int)info->pos.y)
		draw_mm_buf(info, mm, 0X00FFD700);
	else if (info->map[mm->map_i][mm->map_j] == 4)
		draw_mm_buf(info, mm, 0X0088C7DC);
	else
		draw_mm_buf(info, mm, 0X00000000);
}

void	draw_mini_map(t_info *info)
{
	t_mini_map	mm;

	mm.map_i = 0;
	mm.mm_i = 5;
	mm.mm_hght = info->hght / 6;
	mm.mm_wid = info->wid / 6;
	while (mm.mm_i < mm.mm_hght && mm.map_i < info->row_count)
	{
		mm.hght_cnt = 0;
		while (mm.hght_cnt < mm.mm_hght / info->row_count)
		{
			mm.map_j = 0;
			mm.mm_j = 5;
			while (mm.mm_j < mm.mm_wid && mm.map_j < info->col_count)
			{
				mm.wid_cnt = 0;
				draw_items(info, &mm);
				mm.map_j++;
			}
			mm.hght_cnt++;
			mm.mm_i++;
		}
		mm.map_i++;
	}
}
