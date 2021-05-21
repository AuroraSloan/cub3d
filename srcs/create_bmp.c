/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  create_bmp.c                                         :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/13 21:00:55 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/21 22:42:38 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static void	create_bmfh(t_info *info, int fd)
{
	unsigned int	pixel_data_offset;
	unsigned int	file_size;

	pixel_data_offset = 14;
	file_size = pixel_data_offset + info->wid * info->hght * 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &pixel_data_offset, 4);
}

static void	create_bmih(t_info *info, int fd)
{
	unsigned int	info_header_size;
	unsigned int	color_planes;
	unsigned int	bits_per_pixel;
	int				pixels_per_meter;

	info_header_size = 40;
	color_planes = 1;
	bits_per_pixel = 32;
	pixels_per_meter = 0;
	write(fd, &info_header_size, 4);
	write(fd, &info->wid, 4);
	write(fd, &info->hght, 4);
	write(fd, &color_planes, 2);
	write(fd, &bits_per_pixel, 2);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
	write(fd, &pixels_per_meter, 4);
	write(fd, &pixels_per_meter, 4);
	write(fd, "\0\0\0\0\0\0\0\0", 8);
}

static void	write_rpd(t_info *info, int fd)
{
	unsigned int	pixel;
	int				x;
	int				y;

	y = info->hght - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < info->wid)
		{
			pixel = info->buf[y][x];
			write(fd, &pixel, 4);
			x++;
		}
		y--;
	}
}

void	create_bmp(t_info *info, char *file_name)
{
	int	fd;

	info->bmp = 1;
	fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	check_failed_fd(info, fd);
	create_bmfh(info, fd);
	create_bmih(info, fd);
	configure_image(info);
	write_rpd(info, fd);
	close(fd);
	successful_exit(info);
}
