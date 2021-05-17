/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  init_game_bonus.c                                    :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/13 21:24:35 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:17:07 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../libraries/libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void	init_pointers_keys(t_info *info)
{
	info->mlx = NULL;
	info->img.img = NULL;
	info->win = NULL;
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->s_path = NULL;
	info->sp_buf = NULL;
	info->sp_dist = NULL;
	info->sp_ordr = NULL;
	info->sprt = NULL;
	info->key.up = 0;
	info->key.down = 0;
	info->key.left = 0;
	info->key.right = 0;
	info->key.w = 0;
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;
}

void	init_sprite_info(t_info *info)
{
	info->sp_buf = (double *)malloc(sizeof(double) * info->wid);
	if (!(info->sp_buf))
		free_exit(info, "Memory allocation error");
	info->sp_dist = (double *)malloc(sizeof(double) * info->sp_count);
	if (!(info->sp_dist))
		free_exit(info, "Memory allocation error");
	info->sp_ordr = (int *)malloc(sizeof(int) * info->sp_count);
	if (!(info->sp_ordr))
		free_exit(info, "Memory allocation error");
	info->sprt = (t_d_vec *)malloc(sizeof(t_d_vec) * info->sp_count);
	if (!(info->sprt))
		free_exit(info, "Memory allocation error");
}

void	init_buf(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->buf = (int **)malloc(sizeof(int *) * info->hght);
	if (!(info->buf))
		free_exit(info, "Memory allocation error");
	info->buf_flag++;
	while (i < info->hght)
	{
		info->buf[i] = (int *)malloc(sizeof(int) * info->wid);
		if (!(info->buf[i]))
			free_exit(info, "Memory allocation error");
		info->buf_flag++;
		i++;
	}
	i = 0;
	while (i < info->hght)
	{
		j = 0;
		while (j < info->wid)
			info->buf[i][j++] = 0;
		i++;
	}
}

static void	count_col(t_info *info, char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > info->col_count)
		info->col_count = len;
}

void	count_map_rows(t_info *info)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	fd = open(info->name, O_RDONLY);
	check_failed_fd(info, fd);
	while (is_not_map(line, fd, info))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		check_failed_ret(info, line, fd, ret);
	}
	while (!(is_not_map(line, fd, info)))
	{
		info->row_count++;
		count_col(info, line);
		safe_free(line);
		ret = get_next_line(fd, &line);
		if (ret == -1)
			free_line(info, fd, line, "memory error");
	}
	safe_free(line);
	close(fd);
}
