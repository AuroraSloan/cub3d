/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  draw_sprites_bonus.c                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:36:41 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/21 22:39:49 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <math.h>

static void	locate_sprites(t_info *info)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < info->row_count)
	{
		j = 0;
		while (j < info->col_count)
		{
			if (info->map[i][j] == 2 || info->map[i][j] == 3
				|| info->map[i][j] == 4)
			{	
				init_sptext_info(info, i, j, count);
				info->sprt[count].x = i + .5;
				info->sprt[count].y = j + .5;
				count++;
			}
			j++;
		}
		i++;
	}
}

static void	calc_sprite_dist(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->sp_count)
	{
		info->sp_ordr[i] = i;
		info->sp_dist[i] = ((info->pos.x - info->sprt[i].x)
				* (info->pos.x - info->sprt[i].x)
				+ (info->pos.y - info->sprt[i].y)
				* (info->pos.y - info->sprt[i].y));
		i++;
	}
}

static void	calc_sprite_info(t_info *info, t_sprite *s)
{
	s->inv_det = 1.0 / (info->cam.x * info->dir.y
			- info->dir.x * info->cam.y);
	s->mod.x = s->inv_det * (info->dir.y * s->loc.x
			- info->dir.x * s->loc.y);
	s->mod.y = s->inv_det * (-info->cam.y * s->loc.x
			+ info->cam.x * s->loc.y);
	s->screen = (int)((info->wid / 2) * (1 + s->mod.x / s->mod.y));
	s->mv_screen = (int)(0.0 / s->mod.y);
	s->hght = (int)fabs((info->hght / s->mod.y) / 1);
	s->draw_start.y = -s->hght / 2 + info->hght / 2 + 0.0;
	if (s->draw_start.y < 0)
		s->draw_start.y = 0;
	s->draw_end.y = s->hght / 2 + info->hght / 2 + 0.0;
	if (s->draw_end.y >= info->hght)
		s->draw_end.y = info->hght - 1;
	s->wid = (int)fabs((info->hght / s->mod.y) / 1);
	s->draw_start.x = -s->wid / 2 + s->screen;
	if (s->draw_start.x < 0)
		s->draw_start.x = 0;
	s->draw_end.x = s->wid / 2 + s->screen;
	if (s->draw_end.x >= info->wid)
		s->draw_end.x = info->wid - 1;
}

static void	configure_sprite(t_info *info, t_sprite s, int stripe, int i)
{
	while (stripe < s.draw_end.x)
	{
		s.tex.x = (int)((256 * (stripe - (-s.wid / 2 + s.screen))
					* TEX_WID / s.wid) / 256);
		if (s.mod.y > 0 && stripe > 0 && stripe < info->wid
			&& s.mod.y < info->sp_buf[stripe])
		{
			s.col = s.draw_start.y;
			while (s.col < s.draw_end.y)
			{
				s.d = (s.col - s.mv_screen) * 256 - info->hght
					* 128 + s.hght * 128;
				s.tex.y = ((s.d * TEX_HGHT) / s.hght) / 256;
				s.color = info->texture[info->sp_tex[i]][TEX_WID
					* s.tex.y + s.tex.x];
				if ((s.color & 0X00FFFFFF) != 0)
					info->buf[s.col][stripe] = s.color;
				s.col++;
			}
		}
		stripe++;
	}
}

void	draw_sprites(t_info *info)
{
	t_sprite	s;
	int			i;
	int			stripe;

	i = 0;
	locate_sprites(info);
	calc_sprite_dist(info);
	sort_sprites(info);
	while (i < info->sp_count)
	{
		s.loc.x = info->sprt[info->sp_ordr[i]].x - info->pos.x;
		s.loc.y = info->sprt[info->sp_ordr[i]].y - info->pos.y;
		calc_sprite_info(info, &s);
		stripe = s.draw_start.x;
		configure_sprite(info, s, stripe, i);
		i++;
	}
}
