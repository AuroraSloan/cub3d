/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompso <jthomps@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:21 by jthompso          #+#    #+#             */
/*   Updated: 2021/05/09 21:15:05 by jthompso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include "../libraries/libmlx_Linux/mlx.h"
#include <math.h>
/*for open*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*for close*/
#include <unistd.h>

#include <stdint.h>

void	safe_free(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_paths(t_info *info)
{
	if (info->no_path != NULL)
		safe_free(info->no_path);
	if (info->so_path != NULL)
		safe_free(info->so_path);	
	if (info->we_path != NULL)
		safe_free(info->we_path);
	if (info->ea_path != NULL)
		safe_free(info->ea_path);
	if (info->s_path != NULL)
		safe_free(info->s_path);
}

void	free_matrices(t_info *info)
{
	int i;

	i = 0;	
	if (info->map_flag >= 0)
	{	
		while (i < info->row)
			safe_free(info->map[i++]);
		safe_free(info->map);
	}
	i = 0;
	if (info->texture_flag >= 0)
	{	
		while (i < 5)
			safe_free(info->texture[i++]);
		safe_free(info->texture);
	}
	i = 0;
	if (info->buf_flag >= 0)
	{	
		while (i < info->hght)
			safe_free(info->buf[i++]);
		safe_free(info->buf);
	}	
}

void		free_memory(t_info *info)
{
	free_paths(info);
	free_matrices(info);
	if (info->img.img != NULL)
		mlx_destroy_image(info->mlx, info->img.img);	
	if (info->win != NULL)
		mlx_destroy_window(info->mlx, info->win);
	if (info->mlx != NULL)
	{
		mlx_destroy_display(info->mlx);
		mlx_loop_end(info->mlx);
		safe_free(info->mlx);
	}
}

int		successful_exit(t_info *info, int flag)
{
	free_memory(info);
	if (flag == 0)
		printf("See you next time!\n");
	else
		printf("The image cub3D.bmp was successfully created\n");
	exit(EXIT_SUCCESS);
}

void	failed_exit(char *exit_status)
{	
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(exit_status, 2);
	exit(EXIT_FAILURE);
}

void	free_exit(t_info *info, char *exit_status)
{
	free_memory(info);
	failed_exit(exit_status);
}

void	free_line(t_info *info, int fd, char *line, char *exit_status)
{
	safe_free(line);
	close(fd);
	free_exit(info, exit_status);
}

void	l_r_turn(t_info *info)
{
	if (info->key.left)
	{
		info->old_dir = info->dir.x;
		info->dir.x = info->dir.x * cos(-info->rot_spd) - info->dir.y * sin(-info->rot_spd);
		info->dir.y = info->old_dir * sin(-info->rot_spd) + info->dir.y * cos(-info->rot_spd);
		info->old_cam = info->cam.x;
		info->cam.x = info->cam.x * cos(-info->rot_spd) - info->cam.y * sin(-info->rot_spd);
		info->cam.y = info->old_cam * sin(-info->rot_spd) + info->cam.y * cos(-info->rot_spd);
	}
	if (info->key.right)
	{
		info->old_dir = info->dir.x;
		info->dir.x = info->dir.x * cos(info->rot_spd) - info->dir.y * sin(info->rot_spd);
		info->dir.y = info->old_dir * sin(info->rot_spd) + info->dir.y * cos(info->rot_spd);
		info->old_cam = info->cam.x;
		info->cam.x = info->cam.x * cos(info->rot_spd) - info->cam.y * sin(info->rot_spd);
		info->cam.y = info->old_cam * sin(info->rot_spd) + info->cam.y * cos(info->rot_spd);
	}
}

void	l_r_move(t_info *info)
{
	if (info->key.a)
	{
		if (!info->map[(int)(info->pos.x - info->cam.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y - info->cam.y * info->mv_spd)])
			info->pos.y -= info->cam.y * info->mv_spd;
	}	
	if (info->key.d)	
	{
		if (!info->map[(int)(info->pos.x + info->cam.x * info->mv_spd)][(int)(info->pos.y)])	
			info->pos.x += info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y + info->cam.y * info->mv_spd)])
			info->pos.y += info->cam.y * info->mv_spd;
	}
}

void	f_b_move(t_info *info)
{
	if (info->key.w)
	{
		if (!info->map[(int)(info->pos.x + info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y + info->dir.y * info->mv_spd)])
			info->pos.y += info->dir.y * info->mv_spd;
	}	
	if (info->key.s)
	{
		if (!info->map[(int)(info->pos.x - info->dir.x * info->mv_spd)][(int)(info->pos.y)])	
			info->pos.x -= info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y - info->dir.y * info->mv_spd)])
			info->pos.y -= info->dir.y * info->mv_spd;
	}
}

void	set_controls(t_info *info)
{
	l_r_turn(info);
	l_r_move(info);
	f_b_move(info);
}

int		key_press(int keycode, t_info *info)
{	
	if (keycode == ESC)
		successful_exit(info, 0);
	else if (keycode == UP)
		info->key.up = 1;
	else if (keycode == DWN)
		info->key.down = 1;
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
int		key_release(int keycode, t_info *info)
{	
	if (keycode == ESC)
		successful_exit(info, 0);
	else if (keycode == UP)
		info->key.up = 0;
	else if (keycode == DWN)
		info->key.down = 0;
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

void	cub_check(t_info *info, char *filename)
{
	int	start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".cub", 4) != 0)
		failed_exit("The second argument should be a .cub file");
	info->name = filename;
}

void	compare_resolution(t_info *info)
{
	int	screen_width;
	int	screen_hight;

	mlx_get_screen_size(info->mlx, &screen_width, &screen_hight);
	if (info->wid > screen_width)
		info->wid = screen_width;
	if (info->hght > screen_hight)
		info->hght = screen_hight;
}

int	is_not_map(char *line)
{
	if (line == NULL)
		return (1);
	if (line[0] == '1' || line[0] == ' ')
		return (0);
	return (1);
}

void	init_resolution(t_info *info, char *line, int fd)
{	
	int		i;
	
	i = 0;	
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	info->wid = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]) && line[i])
		i++;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	info->hght = ft_atoi(&line[i]);
	if (info->wid <= 0 || info->hght <= 0)
		free_line(info, fd, line, "Resolution must be a positive integer greater than 0");
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		get_next_color(t_info *info, int fd, char *line, int i)
{
	while (ft_isdigit(line[i]) && line[i]) 
		i++;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	if (line[i] == '\0')
		free_line(info, fd, line, "Must have red, green, and blue colors");
	return (i);
}

int		init_c_f_color(t_info *info, char *line, int fd)
{
	int		i;
	int		red;
	int		green;
	int		blue;

	i = 0;	
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	if (line[i] == '\0')
		free_line(info, fd, line, "Must have red, green, and blue");
	red = ft_atoi(&line[i]);
	i = get_next_color(info, fd, line, i);
	green = ft_atoi(&line[i]);	
	i = get_next_color(info, fd, line, i);
	blue = ft_atoi(&line[i]);	
	if (red < 0 || green < 0 || blue < 0)
		free_line(info, fd, line, "color must be positive int");
	if (red > 255 || green > 255 || blue > 255)
		free_line(info, fd, line, "color ints must be less than 255");
	return (create_trgb(255, red, green, blue));
}

void	init_paths(t_info *info, char *line, int fd)
{
	if (memcmp(line, "NO", 2) == 0)
	{
		if (!(info->no_path = ft_strtrim(&line[2], " ")))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "SO", 2) == 0)
	{	
		if (!(info->so_path = ft_strtrim(&line[2], " ")))
			free_line(info, fd, line, "can't allocate");	
	}
	else if (memcmp(line, "WE", 2) == 0)
	{
		if (!(info->we_path = ft_strtrim(&line[2], " ")))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "EA", 2) == 0)
	{
		if (!(info->ea_path = ft_strtrim(&line[2], " ")))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "S", 1) == 0)
	{
		if (!(info->s_path = ft_strtrim(&line[1], " ")))
			free_line(info, fd, line, "can't allocate");
	}	
}

void	floodfill(t_info *info, int tmp_map[info->row_count][info->col_count], int x, int y)
{
//	printf("x: %d, y: %d\n", x, y);
	if (x == 0 || x >= info->row_count || y <= 0 || y == info->col_count)	
		free_exit(info, "map is not closed");
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

void	check_closed_map(t_info *info, int x, int y)
{
	int tmp_map[info->row_count][info->col_count];
	int i;
	int j;

	i = 0;
	while (i < info->row_count)
	{
		j = 0;
		while (j < info->col_count)
		{
			tmp_map[i][j] = info->map[i][j];
			printf("%d", tmp_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}	
	floodfill(info, tmp_map, x, y);
}

void	cub_info_check(t_info *info)
{	
	if (!info->wid || !info->hght)
		free_exit(info, "Missing .cub resolution info");
	if (!info->no_path)
		free_exit(info, "Missing .cub north path info");	
	if (!info->so_path)
		free_exit(info, "Missing .cub south path info");
	if (!info->we_path)
		free_exit(info, "Missing .cub west path info");
	if (!info->ea_path)
		free_exit(info, "Missing .cub east path info");
	if (!info->s_path)
		free_exit(info, "Missing .cub sprite path info");
	if (!info->f_color)
		free_exit(info, "Missing .cub floor color info");
	if (!info->c_color)
		free_exit(info, "Missing ceiling color info");	
	check_closed_map(info, (int)info->pos.x, (int)info->pos.y);
	//add floor and ceiling paths if able to do that.
}

int		is_start(char strt)
{	
	return(strt == 'N' || strt == 'S' || strt == 'E' || strt == 'W');
}

void	init_n_s_vectors(t_info *info)
{
	if (info->start == 'N')
	{
		info->dir.x = -1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = -0.66;
	}
	else if (info->start == 'S')
	{
		info->dir.x = 1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = 0.66;
	}
}

void	init_w_e_vectors(t_info *info)
{
	if (info->start == 'E')
	{
		info->dir.x = 0.0;
		info->dir.y = -1.0;
		info->cam.x = .66;
		info->cam.y = 0.0;
	}
	else if (info->start == 'W')
	{
		info->dir.x = 0.0;
		info->dir.y = 1.0;
		info->cam.x = -0.66;
		info->cam.y = 0.0;
	}
}

void	set_start(t_info *info, char strt)
{	
	info->start = strt;
	info->pos.x = info->row + .5;
	info->pos.y = info->col + .5;
	if (info->start == 'N' || info->start == 'S')
		init_n_s_vectors(info);
	else if (info->start == 'W' || info->start == 'E')
		init_w_e_vectors(info);	
	info->map[info->row][info->col] = 0;
}

void	init_map_row(t_info *info, int fd, char * line, int row)
{
	int len;
	int tmp;

	info->col = 0;
	len = ft_strlen(line);
	if (!(info->map[info->row] = (int *)malloc(sizeof(int) * info->col_count)))
		free_line(info, fd, line, "Memory allocation error");
	info->map_flag++;
	tmp = len;
	len--;
	while (tmp < info->col_count)
	{
		info->map[info->row][info->col++] = 0;
		//printf("%d", info->map[info->row][info->col]);
		tmp++;
	}
	while (len >= 0)
	{
		if (is_start(line[len]))
			set_start(info, line[len]);
		else if ((line[len] == ' ' && row == 0))
			info->map[info->row][info->col] = 1;
		else if (line[len] == ' ')
			info->map[info->row][info->col] = 0;
		else 
			info->map[info->row][info->col] = line[len] - '0';	
		if (info->map[info->row][info->col] > 2)
			free_line(info, fd, line, "invalid character in map");	
		//printf("%d", info->map[info->row][info->col]);
		info->col++;
		len--;
	}	
	while (info->col < info->col_count)
	{	
		info->map[info->row][info->col] = 0;
		//printf("%d", info->map[info->row][info->col]);
		info->col++;
	}
	//printf("\n");
}

void	init_map(int ret, t_info *info, int fd, char *line)
{
	info->start = '\0';
	info->row = 0;
	if (!(info->map = (int **)malloc(sizeof(int *) * info->row_count)))
		free_line(info, fd, line, "Memory allocation error");
	info->map_flag++;
	while (ret != 0)
	{	
		init_map_row(info, fd, line, info->row);
		safe_free(line);
		if ((ret = get_next_line(fd, &line)) == -1)
			free_line(info, fd, line, "cannot read .cub file");
		info->row++;
	}
	if (!info->start)
		free_line(info, fd, line, "No start position info");
	safe_free(line);
	close(fd);	
}

void	parse_line_info(t_info *info, int fd, char *line)
{
	if (line[0] == 'R')
		init_resolution(info, line, fd);
	else if (line[0] == 'F')
		info->f_color = init_c_f_color(info, line, fd);
	else if (line[0] == 'C')
		info->c_color = init_c_f_color(info, line, fd);
	else
		init_paths(info, line, fd);	
}

void	parse_cub_info(t_info *info)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	if ((fd = open(info->name, O_RDONLY)) == -1)
		failed_exit("Could not open .cub file");
	while (is_not_map(line))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		if (ret == 0)
			free_line(info, fd, line, "check map info");
		if (ret == -1)
			free_line(info, fd, line, "memory error");
		parse_line_info(info, fd, line);
	}
	init_map(ret, info, fd, line);	
}

void		my_pxl_put(t_img *img, int x, int y, int color)
{
	int *dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	init_ray_information(t_info *info, t_ray *r, int stripe)
{
	r->cam_x = 2 * stripe / (double)info->wid - 1;
	r->dir.x = info->dir.x + info->cam.x * r->cam_x;
	r->dir.y = info->dir.y + info->cam.y * r->cam_x;
	r->map.x = (int)info->pos.x;	
	r->map.y = (int)info->pos.y;	
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	r->hit = 0;
}

void	digital_differential_analyzer(t_info *info, t_ray *r)
{	
	while (r->hit == 0)
	{
		if (r->side_dist.x < r->side_dist.y)
		{
			r->side_dist.x += r->delta_dist.x;
			r->map.x += r->step.x;
			r->side = 0;
		}
		else
		{
			r->side_dist.y += r->delta_dist.y;
			r->map.y += r->step.y;
			r->side = 1;
		}
		if (info->map[(int)r->map.x][(int)r->map.y] == 1)
			r->hit = 1;
	}	
}

void	calculate_ray_distance(t_info *info, t_ray *r)
{
	if (r->side == 0)
		r->dist = (r->map.x - info->pos.x + (1 - r->step.x) / 2) / r->dir.x;
	else
		r->dist = (r->map.y - info->pos.y + (1 - r->step.y) / 2) / r->dir.y;	
}

void	set_ray_distance(t_info *info, t_ray *r)
{
	if (r->dir.x < 0)
	{
		r->step.x = -1;
		r->side_dist.x = (info->pos.x - r->map.x) * r->delta_dist.x;
	}
	else
	{
		r->step.x = 1;
		r->side_dist.x = (r->map.x + 1.0 - info->pos.x) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step.y = -1;
		r->side_dist.y = (info->pos.y - r->map.y) * r->delta_dist.y;
	}
	else
	{
		r->step.y = 1;
		r->side_dist.y = (r->map.y + 1.0 - info->pos.y) * r->delta_dist.y;
	}
	digital_differential_analyzer(info, r);
	calculate_ray_distance(info, r);
}

void	calculate_wall_height(t_info *info, t_ray *r)
{
	r->wall_hight = (int)(info->hght / r->dist);
	r->draw_start = -r->wall_hight / 2 + info->hght / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->wall_hight / 2 + info->hght / 2;
	if (r->draw_end >= info->hght)
		r->draw_end = info->hght - 1;	
}

void	select_which_texture(t_info *info, t_ray *r)
{
	if (r->side == 0 && r->step.x < 0)
		info->tex_num = 0;
	else if (r->side == 0 && r->step.x > 0)
		info->tex_num = 1;
	else if (r->side == 1 && r->step.y > 0)
		info->tex_num = 2;
	else if (r->side == 1 && r->step.y < 0)
		info->tex_num = 3;
}

void	calculate_texture_stripe(t_info *info, t_ray *r)
{
	if (r->side == 0)
		info->wall_x = info->pos.y + r->dist * r->dir.y;
	else
		info->wall_x = info->pos.x + r->dist * r->dir.x;	
	info->wall_x -= floor(info->wall_x);
	info->tex.x = (int)(info->wall_x * (double)TEX_WID);
	if (r->side == 0 && r->dir.x > 0)
		info->tex.x = TEX_WID - info->tex.x - 1;
	if (r->side == 1 && r->dir.y < 0)
		info->tex.x = TEX_WID - info->tex.x - 1;
	info->step_y = 1.0 * TEX_HGHT / r->wall_hight;
	info->tex_pos = (r->draw_start - info->hght / 2 + r->wall_hight / 2) * info->step_y;
}

void	draw_buffer(t_info *info, t_ray r, int stripe)
{
	int	sky;
	int	floor;
	int	wall;
	int	pixel;

	sky = 0;
	while (sky < r.draw_start)
		info->buf[sky++][stripe] = info->c_color;
	wall = r.draw_start;
	while (wall < r.draw_end)
	{	
		info->tex.y = (int)info->tex_pos & (TEX_HGHT - 1);
		info->tex_pos += info->step_y;
		pixel = info->texture[info->tex_num][TEX_HGHT * info->tex.y + info->tex.x];
		info->buf[wall][stripe] = pixel;	
		wall++;
	}	
	floor = r.draw_end;
	while (floor < info->hght)
		info->buf[floor++][stripe] = info->f_color;
}

void	configure_image(t_info *info)
{
	t_ray	r;
	int	stripe;

	stripe = 0;
	while(stripe < info->wid)
	{
		init_ray_information(info, &r, stripe);
		set_ray_distance(info, &r);
		calculate_wall_height(info, &r);
		select_which_texture(info, &r);
		calculate_texture_stripe(info, &r);
		draw_buffer(info, r, stripe);
		stripe++;
	}
}

void	draw_image(t_info *info)
{
	int x;
	int y;

	y = 0;
	while (y < info->hght)
	{
		x = 0;
		while (x < info->wid)
		{
			info->img.addr[y * info->wid + x] = info->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

int		game_loop(t_info *info)
{
	set_controls(info);	
	configure_image(info);	
	draw_image(info);
	return(0);
}

void		load_image(t_info *info, int *texture, char *path, t_tex *tex)
{	
	if (!(tex->img = mlx_xpm_file_to_image(info->mlx, path, &tex->wid, &tex->hght)))
		free_exit(info, "recheck image paths");
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->end);
	for (int y = 0; y < tex->hght; y++)
	{
		for (int x = 0; x < tex->wid; x++)
		{
			texture[tex->wid * y + x] = tex->addr[tex->wid * y + x];
		}
	}
	mlx_destroy_image(info->mlx, tex->img);	
}

void		load_textures(t_info *info)
{
	t_tex tex;

	load_image(info, info->texture[0], info->no_path, &tex);
	load_image(info, info->texture[1], info->so_path, &tex);
	load_image(info, info->texture[2], info->we_path, &tex);
	load_image(info, info->texture[3], info->ea_path, &tex);
	load_image(info, info->texture[4], info->s_path, &tex);
//	load_image(info, info->texture[5], info->f_path, &tex);
//	load_image(info, info->texture[6], into->c_path, &tex);
}

void	init_buf(t_info *info)
{
	int i;
	int j;

	i = 0;
	if (!(info->buf = (int **)malloc(sizeof(int *) * info->hght)))
		free_exit(info, "Memory allocation error");
	info->buf_flag++;
	while (i < info->hght)
	{
		if (!(info->buf[i++] = (int *)malloc(sizeof(int) * info->wid)))
			free_exit(info, "Memory allocation error");
		info->buf_flag++;
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

void	init_textures(t_info *info)
{
	int i;
	int j;

	i = 0;
	if (!(info->texture = (int **)malloc(sizeof(int *) * 5)))
		free_exit(info, "Memory allocation error");
	info->texture_flag++;
	while (i < 5)
	{
		if (!(info->texture[i++] = (int *)malloc(sizeof(int) * (TEX_HGHT * TEX_WID))))
			free_exit(info, "Memory allocaiton error");
		info->texture_flag++;
	}
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < TEX_HGHT * TEX_WID)
			info->texture[i][j++] = 0;
		i++;
	}
}

void	init_keys(t_info *info)
{
	info->key.up = 0;
	info->key.down = 0;
	info->key.left = 0;
	info->key.right = 0;
	info->key.w = 0;
	info->key.a = 0;
	info->key.s = 0;
	info->key.d = 0;
}

void	count_map_rows(t_info *info)
{
	char	*line;
	int		fd;
	int		ret;
	int		len;

	info->row_count = 0;
	info->col_count = 0;
	line = NULL;
	if ((fd = open(info->name, O_RDONLY)) == -1)
		failed_exit("Could not open .cub file");
	while (is_not_map(line))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);	
		if (ret == 0)
			free_line(info, fd, line, "check map info");
		if (ret == -1)
			free_line(info, fd, line, "memory error");
	}
	while (!(is_not_map(line)))//(ret = get_next_line(fd, &line) != 0))
	{
		info->row_count++;
		len = ft_strlen(line);
		if (len > info->col_count)
			info->col_count = len;
		safe_free(line);
		if ((ret = get_next_line(fd, &line) == -1))
			free_line(info, fd, line, "memory error");	
	}	
	safe_free(line);
	close(fd);	
}

void	init_pointers(t_info *info)
{
	info->mlx = NULL;
	info->img.img = NULL;
	info->win = NULL;	
	info->no_path = NULL;
	info->so_path = NULL;
	info->we_path = NULL;
	info->ea_path = NULL;
	info->s_path = NULL;
}

void	init_game(t_info *info)
{	
	info->map_flag = -1;
	info->buf_flag = -1;
	info->texture_flag = -1;
	init_pointers(info);
	count_map_rows(info);
	parse_cub_info(info);	
	cub_info_check(info);	
	if (!(info->mlx = mlx_init()))
		free_exit(info, "Connection to X-server Failed");	
	compare_resolution(info);
	init_buf(info);	
	init_textures(info);	
	load_textures(info);	
	init_keys(info);
	info->mv_spd = .015;
	info->rot_spd = .015;
}

void	create_bmfh(t_info *info, int fd)
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

void	create_bmih(t_info *info, int fd)
{
	unsigned int	info_header_size;
	unsigned int	color_planes;
	unsigned int	bits_per_pixel;

	info_header_size = 12;
	color_planes = 1;
	bits_per_pixel = 32;
	write(fd, &info_header_size, 4);
	write(fd, &info->wid, 2);	
	write(fd, &info->hght, 2);
	write(fd, &color_planes, 2);
	write(fd, &bits_per_pixel, 2);	
}

void	write_rpd(t_info *info, int fd)
{
	uint32_t	pixel;
	int		x;
	int		y;
	
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
	int fd;

	if ((fd = open(file_name, O_WRONLY | O_CREAT , S_IRWXU | S_IRWXG | S_IRWXO)) == -1)
		free_exit(info, "Could not create .bmp file");
	create_bmfh(info, fd);
	create_bmih(info, fd);
	configure_image(info);
	write_rpd(info, fd);
	close(fd);
	successful_exit(info, 1);
}

int		main(int argc, char **argv)
{
	t_info	info;

	if (argc > 3)
		failed_exit("Too many arguments");	
	else if (argc < 2)
		failed_exit("Please select which .cub file to read");
	else if (argc == 3 && (ft_memcmp("--save", argv[2], 6) != 0))
		failed_exit("Second argument should be --save");	
	cub_check(&info, argv[1]);	
	init_game(&info);	
	if (argc == 3 && (ft_memcmp("--save", argv[2], 6) == 0))
		create_bmp(&info, "cub3D.bmp");
	if (!(info.win = mlx_new_window(info.mlx, info.wid, info.hght, "C3D")))
		free_exit(&info, "Could not create window");
	if (!(info.img.img = mlx_new_image(info.mlx, info.wid, info.hght)))
		free_exit(&info, "Could not create image");	
	info.img.addr = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.len, &info.img.end);
	if (argc == 2)
		mlx_loop_hook(info.mlx, game_loop, &info);
	mlx_hook(info.win, 2, 1L << 0, &key_press, &info);
	mlx_hook(info.win, 3, 1L << 1, &key_release, &info);
	mlx_hook(info.win, 33, 1L << 17, &successful_exit, &info);
	if (argc == 2)
		mlx_loop(info.mlx);
}

	
		//START CASTING FLOOR
		/*if (r.sd == 0 && r.dir.x > 0)
		{
			r.floor_wall.x = r.map.x;
			r.floor_wall.y = r.map.y + info->wall; 
		}
		else if (r.sd == 0 && r.dir.x < 0)
		{
			r.floor_wall.x = r.map.x + 1.0;
			r.floor_wall.y = r.map.y + info->wall; 
		}
		else if (r.sd == 1 && r.dir.x > 0)
		{
			r.floor_wall.x = r.map.x + info->wall;
			r.floor_wall.y = r.map.y; 
		}
		else
		{
			r.floor_wall.x = r.map.x + info->wall;
			r.floor_wall.y = r.map.y + 1.0; 
		}
		r.dist_wall = r.dist;
		r.dist_player = 0.0;
		y = r.draw_end + 1;
		while (y < info->hght)
		{
			r.current_dist = info->hght / (2.0 * y - info->hght);
			r.weight = (r.current_dist - r.dist_player) / (r.dist_wall - r.dist_player);
			r.current_floor.x = r.weight * r.floor_wall.x + (1.0 - r.weight) * info->pos.x;
			r.current_floor.y = r.weight * r.floor_wall.y + (1.0 - r.weight) * info->pos.y;
			r.floor_tex.x = (int)(r.current_floor.x * TEX_WID) % TEX_WID;
			r.floor_tex.y = (int)(r.current_floor.y * TEX_HGHT) % TEX_HGHT;
			r.pat = ((int)(r.current_floor.x) + (int)(r.current_floor.y)) & 2;
			if (r.pat == 0)
				r.f_tex = 5;
			else
				r.f_tex = 5;
			//floor
			info->buf[y][x] = (info->texture[r.f_tex][TEX_WID * r.floor_tex.y + r.floor_tex.x] >> 1) & 8355711;
			//ceiling
			info->buf[info->hght - y][x] = info->texture[4][TEX_WID * r.floor_tex.y + r.floor_tex.x];
			y++;
		}*/
