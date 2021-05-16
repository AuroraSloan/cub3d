/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  check_closed_map.c                                   :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 14:37:32 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/16 16:30:29 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdlib.h>

static void	free_tmp_map(t_info *info, int **tmp_map, int cnt, char *error)
{
	int	i;

	i = 0;
	while (i < cnt)
		safe_free(tmp_map[i++]);
	safe_free(tmp_map);
	if (error)
		free_exit(info, error);
}

static void	floodfill(t_info *info, int **tmp_map, int x, int y)
{
	if (x == 0 || x >= info->row_count - 1
		|| y == 0 || y >= info->col_count - 1)
		free_tmp_map(info, tmp_map, info->row_count, "map not closed");
	tmp_map[x][y] = '#';
	if (tmp_map[x - 1][y] != 1 && tmp_map[x - 1][y] != '#')
		floodfill(info, tmp_map, x - 1, y);
	if (tmp_map[x + 1][y] != 1 && tmp_map[x + 1][y] != '#')
		floodfill(info, tmp_map, x + 1, y);
	if (tmp_map[x][y - 1] != 1 && tmp_map[x][y - 1] != '#')
		floodfill(info, tmp_map, x, y -1);
	if (tmp_map[x][y + 1] != 1 && tmp_map[x][y + 1] != '#')
		floodfill(info, tmp_map, x, y + 1);
}

static int	**init_tmp_map(t_info *info)
{
	int	**tmp_map;
	int	cnt;

	cnt = 0;
	tmp_map = (int **)malloc(sizeof(int *) * info->row_count);
	if (!(tmp_map))
		free_exit(info, "Memory allocation error");
	while (cnt < info->row_count)
	{
		tmp_map[cnt] = (int *)malloc(sizeof(int) * info->col_count);
		if (!(tmp_map[cnt]))
			free_tmp_map(info, tmp_map, cnt, "Can't allocate mem");
		cnt++;
	}
	return (tmp_map);
}

void	check_closed_map(t_info *info, int x, int y)
{
	int	**tmp_map;
	int	i;
	int	j;

	tmp_map = init_tmp_map(info);
	i = 0;
	while (i < info->row_count)
	{
		j = 0;
		while (j < info->col_count)
		{
			tmp_map[i][j] = info->map[i][j];
			j++;
		}	
		i++;
	}	
	floodfill(info, tmp_map, x, y);
	free_tmp_map(info, tmp_map, info->row_count, NULL);
}
