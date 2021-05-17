/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  sort_sprites_bonus.c                                 :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 15:39:58 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:19:43 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include <stdlib.h>

static void	arrange_sprites(t_info *info, t_pair *sp)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < info->sp_count)
	{
		j = 0;
		while (j < info->sp_count - 1)
		{
			if (sp[j].first > sp[j + 1].first)
			{
				tmp.first = sp[j].first;
				tmp.second = sp[j].second;
				sp[j].first = sp[j + 1].first;
				sp[j].second = sp[j + 1].second;
				sp[j + 1].first = tmp.first;
				sp[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(t_info *info)
{
	t_pair	*sp;
	int		i;

	i = 0;
	sp = (t_pair *)malloc(sizeof(t_pair) * info->sp_count);
	if (!(sp))
		free_exit(info, "could not allocate memory");
	while (i < info->sp_count)
	{
		sp[i].first = info->sp_dist[i];
		sp[i].second = info->sp_ordr[i];
		i++;
	}
	arrange_sprites(info, sp);
	i = 0;
	while (i < info->sp_count)
	{
		info->sp_dist[i] = sp[info->sp_count - i - 1].first;
		info->sp_ordr[i] = sp[info->sp_count - i - 1].second;
		i++;
	}
	safe_free(sp);
}
