/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  sort_sprites_bonus.c                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:39:58 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/21 22:37:56 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <stdlib.h>

static void	set_order(t_arrange *sp, int j)
{
	t_arrange	tmp;

	tmp.a = sp[j].a;
	tmp.b = sp[j].b;
	tmp.c = sp[j].c;
	sp[j].a = sp[j + 1].a;
	sp[j].b = sp[j + 1].b;
	sp[j].c = sp[j + 1].c;
	sp[j + 1].a = tmp.a;
	sp[j + 1].b = tmp.b;
	sp[j + 1].c = tmp.c;
}

static void	arrange_sprites(t_info *info, t_arrange *sp)
{	
	int	i;
	int	j;

	i = 0;
	while (i < info->sp_count)
	{
		j = 0;
		while (j < info->sp_count - 1)
		{
			if (sp[j].a > sp[j + 1].a)
				set_order(sp, j);
			j++;
		}
		i++;
	}
}

void	sort_sprites(t_info *info)
{
	t_arrange	*sp;
	int			i;

	i = 0;
	sp = (t_arrange *)malloc(sizeof(t_arrange) * info->sp_count);
	if (!(sp))
		free_exit(info, "could not allocate memory");
	while (i < info->sp_count)
	{
		sp[i].a = info->sp_dist[i];
		sp[i].b = info->sp_ordr[i];
		sp[i].c = info->sp_tex[i];
		i++;
	}
	arrange_sprites(info, sp);
	i = 0;
	while (i < info->sp_count)
	{
		info->sp_dist[i] = sp[info->sp_count - i - 1].a;
		info->sp_ordr[i] = sp[info->sp_count - i - 1].b;
		info->sp_tex[i] = sp[info->sp_count - i - 1].c;
		i++;
	}
	safe_free(sp);
}
