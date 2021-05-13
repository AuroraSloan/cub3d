/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompso <jthomps@student.42tokyo.jp>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 15:19:21 by jthompso          #+#    #+#             */
/*   Updated: 2021/05/13 16:42:44 by jthompso         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (info->map_flag >= 0)
	{
		while (i < info->map_flag)
			safe_free(info->map[i++]);
		safe_free(info->map);
	}
	i = 0;
	if (info->texture_flag >= 0)
	{
		while (i < info->texture_flag)
			safe_free(info->texture[i++]);
		safe_free(info->texture);
	}
	i = 0;
	if (info->buf_flag >= 0)
	{
		while (i < info->buf_flag)
			safe_free(info->buf[i++]);
		safe_free(info->buf);
	}
}

void	free_memory(t_info *info)
{
	free_paths(info);
	free_matrices(info);
	if (info->sp_buf != NULL)
		safe_free(info->sp_buf);
	if (info->sp_dist != NULL)
		safe_free(info->sp_dist);
	if (info->sp_ordr != NULL)
		safe_free(info->sp_ordr);
	if (info->sprt != NULL)
		safe_free(info->sprt);
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

int	successful_exit(t_info *info, int mssg_flag)
{
	free_memory(info);
	if (mssg_flag == 0)
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

void	turn_left(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(info->rot_spd)
		- info->dir.y * sin(info->rot_spd);
	info->dir.y = old_dir * sin(info->rot_spd)
		+ info->dir.y * cos(info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(info->rot_spd)
		- info->cam.y * sin(info->rot_spd);
	info->cam.y = old_cam * sin(info->rot_spd)
		+ info->cam.y * cos(info->rot_spd);
}

void	turn_right(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(-info->rot_spd)
		- info->dir.y * sin(-info->rot_spd);
	info->dir.y = old_dir * sin(-info->rot_spd)
		+ info->dir.y * cos(-info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(-info->rot_spd)
		- info->cam.y * sin(-info->rot_spd);
	info->cam.y = old_cam * sin(-info->rot_spd)
		+ info->cam.y * cos(-info->rot_spd);
}

void	move_left_right(t_info *info)
{
	if (info->key.a)
	{
		if (!info->map[(int)(info->pos.x
				- info->cam.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				- info->cam.y * info->mv_spd)])
			info->pos.y -= info->cam.y * info->mv_spd;
	}
	if (info->key.d)
	{
		if (!info->map[(int)(info->pos.x
				+ info->cam.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->cam.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				+ info->cam.y * info->mv_spd)])
			info->pos.y += info->cam.y * info->mv_spd;
	}
}

void	move_forwrd_backwrd(t_info *info)
{
	if (info->key.w)
	{
		if (!info->map[(int)(info->pos.x
				+ info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				+ info->dir.y * info->mv_spd)])
			info->pos.y += info->dir.y * info->mv_spd;
	}
	if (info->key.s)
	{
		if (!info->map[(int)(info->pos.x
				- info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y
				- info->dir.y * info->mv_spd)])
			info->pos.y -= info->dir.y * info->mv_spd;
	}
}

void	move_player(t_info *info)
{
	if (info->key.left)
		turn_left(info);
	if (info->key.right)
		turn_right(info);
	move_left_right(info);
	move_forwrd_backwrd(info);
}

int	key_press(int keycode, t_info *info)
{
	if (keycode == ESC)
		successful_exit(info, 0);
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
		successful_exit(info, 0);
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

void	filename_check(t_info *info, char *filename)
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

int	is_valid_game_info(char *line)
{
	int	ret;

	ret = 0;
	if (ft_memcmp(&line[0], "R ", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "NO", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "SO", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "WE", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "EA", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "S ", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "F ", 2) == 0)
		ret = 1;
	else if (ft_memcmp(&line[0], "C ", 2) == 0)
		ret = 1;
	return (ret);
}

int	is_not_map(char *line, int fd, t_info *info)
{
	int	ret;

	if (line == NULL || line[0] == '\0')
		return (1);
	ret = is_valid_game_info(line);
	if (line[0] == '1' || line[0] == ' ' || line[0] == '0')
		return (0);
	if (ret == 0 && line[0] != '1' && line[0] != ' ' && line[0] != '0')
		free_line(info, fd, line, "invalid character in .cub file");
	return (ret);
}

void	init_resolution(t_info *info, char *line, int fd)
{	
	int	i;
	int	tmp;

	i = 0;
	tmp = 0;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	info->wid = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]) && line[i])
		i++;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	info->hght = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]) && line[i])
		i++;
	if (line[i])
		tmp = ft_atoi(&line[i]);
	if (info->wid <= 0 || info->hght <= 0 || tmp != 0)
		free_line(info, fd, line, "Res must be two integers > 0");
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	find_next_color(t_info *info, int fd, char *line, int i)
{
	while ((ft_isdigit(line[i]) && line[i]) || line[i] == '-')
		i++;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	if (line[i] == '\0')
		free_line(info, fd, line, "Must have red green & blue colors");
	return (i);
}

int	find_first_color(t_info *info, int fd, char *line)
{
	int	i;

	i = 0;
	while (!(ft_isdigit(line[i])) && line[i] && line[i] != '-')
		i++;
	if (line[i] == '\0')
		free_line(info, fd, line, "Must have red, green, and blue");
	return (i);
}

int	init_c_f_color(t_info *info, char *line, int fd)
{
	int		i;
	int		rd;
	int		grn;
	int		blu;

	i = find_first_color(info, fd, line);
	rd = ft_atoi(&line[i]);
	i = find_next_color(info, fd, line, i);
	grn = ft_atoi(&line[i]);
	i = find_next_color(info, fd, line, i);
	blu = ft_atoi(&line[i]);
	while ((ft_isdigit(line[i]) && line[i]) || line[i] == '-')
		i++;
	while (line[i] || line[i] == '-')
	{
		if (ft_isdigit(line[i]))
			free_line(info, fd, line, "Too many color integers");
		i++;
	}
	if (rd > 255 || grn > 255 || blu > 255 || rd < 0 || grn < 0 || blu < 0)
		free_line(info, fd, line, "color ints must be 0 - 255");
	return (create_rgb(rd, grn, blu));
}

int	path_filename_check(char *filename)
{
	int	start;

	start = ft_strlen(filename) - 4;
	if (ft_memcmp(&filename[start], ".xpm", 4) != 0)
		return (-1);
	return (1);
}

void	init_ea_s_paths(t_info *info, char *line, int fd)
{
	if (memcmp(line, "EA", 2) == 0)
	{
		if (info->ea_path != NULL)
			free_line(info, fd, line, "Mulptiple EA path info");
		info->ea_path = ft_strtrim(&line[2], " ");
		if (!(info->ea_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "S ", 2) == 0)
	{
		if (info->s_path != NULL)
			free_line(info, fd, line, "Mulptiple S path info");
		info->s_path = ft_strtrim(&line[1], " ");
		if (!(info->s_path))
			free_line(info, fd, line, "can't allocate");
	}
}

void	init_paths(t_info *info, char *line, int fd)
{
	if (memcmp(line, "NO", 2) == 0)
	{
		if (info->no_path != NULL)
			free_line(info, fd, line, "Mulptiple no_path info");
		info->no_path = ft_strtrim(&line[2], " ");
		if (!(info->no_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "SO", 2) == 0)
	{
		if (info->so_path != NULL)
			free_line(info, fd, line, "Mulptiple SO path info");
		info->so_path = ft_strtrim(&line[2], " ");
		if (!(info->so_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (memcmp(line, "WE", 2) == 0)
	{
		if (info->we_path != NULL)
			free_line(info, fd, line, "Mulptiple WE path info");
		info->we_path = ft_strtrim(&line[2], " ");
		if (!(info->we_path))
			free_line(info, fd, line, "can't allocate");
	}
	init_ea_s_paths(info, line, fd);
}

void	floodfill(t_info *info, int tmp_map[info->row_count][info->col_count], int x, int y)
{
	if (x == 0 || x >= info->row_count - 1
		|| y == 0 || y >= info->col_count - 1)
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
	int	tmp_map[info->row_count][info->col_count];
	int	i;
	int	j;

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
}

void	cub_info_check(t_info *info, int fd, char *line)
{
	if (!info->wid || !info->hght)
		free_line(info, fd, line, "Check res info or map location");
	if (!info->no_path)
		free_line(info, fd, line, "Check NO path info or map location");
	if (!info->so_path)
		free_line(info, fd, line, "Check SO path info or map location");
	if (!info->we_path)
		free_line(info, fd, line, "Check WE path info or map location");
	if (!info->ea_path)
		free_line(info, fd, line, "Check EA path info or map location");
	if (!info->s_path)
		free_line(info, fd, line, "Check S path info or map location");
	if (info->f_color == -1)
		free_line(info, fd, line, "Check F color info or map location");
	if (info->c_color == -1)
		free_line(info, fd, line, "Check C color info or map location");
}

int	is_start(char start)
{
	return (start == 'N' || start == 'S' || start == 'E' || start == 'W');
}

void	init_n_s_vectors(t_info *info)
{
	if (info->start == 'N')
	{
		info->dir.x = -1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = 0.66;
	}
	else if (info->start == 'S')
	{
		info->dir.x = 1.0;
		info->dir.y = 0.0;
		info->cam.x = 0.0;
		info->cam.y = -0.66;
	}
}

void	init_w_e_vectors(t_info *info)
{
	if (info->start == 'E')
	{
		info->dir.x = 0.0;
		info->dir.y = 1.0;
		info->cam.x = 0.66;
		info->cam.y = 0.0;
	}
	else if (info->start == 'W')
	{
		info->dir.x = 0.0;
		info->dir.y = -1.0;
		info->cam.x = -.66;
		info->cam.y = 0.0;
	}
}

void	set_start(t_info *info, char start, int fd, char *line)
{
	if (info->start != '\0')
		free_line(info, fd, line, "Multiple start information");
	info->start = start;
	info->pos.x = info->row + .5;
	info->pos.y = info->col + .5;
	if (info->start == 'N' || info->start == 'S')
		init_n_s_vectors(info);
	else if (info->start == 'W' || info->start == 'E')
		init_w_e_vectors(info);
	info->map[info->row][info->col] = 0;
}

void	init_map_row(t_info *info, int fd, char *line)
{
	int	len;

	info->col = 0;
	len = ft_strlen(line);
	info->map[info->row] = (int *)malloc(sizeof(int) * info->col_count);
	if (!(info->map[info->row]))
		free_line(info, fd, line, "Memory allocation error");
	info->map_flag++;
	while (info->col < len)
	{
		if (line[info->col] == '2')
			info->sp_count++;
		if (is_start(line[info->col]))
			set_start(info, line[info->col], fd, line);
		else if (line[info->col] == ' ')
			info->map[info->row][info->col] = 0;
		else
			info->map[info->row][info->col] = line[info->col] - '0';
		if (info->map[info->row][info->col] > 2)
			free_line(info, fd, line, "invalid character in map");
		info->col++;
	}
	while (info->col < info->col_count)
		info->map[info->row][info->col++] = 0;
}

void	init_map(int ret, t_info *info, int fd, char *line)
{
	info->start = '\0';
	info->row = 0;
	info->sp_count = 0;
	info->map = (int **)malloc(sizeof(int *) * info->row_count);
	if (!(info->map))
		free_line(info, fd, line, "Memory allocation error");
	info->map_flag++;
	while (ret != 0)
	{
		if (line[0] == 0)
			free_line(info, fd, line, "Delete new lines after map");
		init_map_row(info, fd, line);
		safe_free(line);
		ret = get_next_line(fd, &line);
		if (ret == -1)
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
	{
		if (info->wid > 0 || info->hght > 0)
			free_line(info, fd, line, "multiple res information");
		init_resolution(info, line, fd);
	}
	else if (line[0] == 'F')
	{
		if (info->f_color > -1)
			free_line(info, fd, line, "Multiple F color info");
		info->f_color = init_c_f_color(info, line, fd);
	}
	else if (line[0] == 'C')
	{
		if (info->c_color > -1)
			free_line(info, fd, line, "Multiple C color info");
		info->c_color = init_c_f_color(info, line, fd);
	}
	else
		init_paths(info, line, fd);
}

void	check_ret(t_info *info, char *line, int fd, int ret)
{
	if (ret == 0)
		free_line(info, fd, line, "check map info");
	if (ret == -1)
		free_line(info, fd, line, "memory error");
}

void	parse_cub_info(t_info *info)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	fd = open(info->name, O_RDONLY);
	if (fd == -1)
		failed_exit("Could not open .cub file");
	while (is_not_map(line, fd, info))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		check_ret(info, line, fd, ret);
		parse_line_info(info, fd, line);
	}
	cub_info_check(info, fd, line);
	compare_resolution(info);
	init_map(ret, info, fd, line);
	check_closed_map(info, (int)info->pos.x, (int)info->pos.y);
}

void	my_pxl_put(t_img *img, int x, int y, int color)
{
	int	*dst;

	dst = img->addr + (y * img->len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
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

void	calculate_ray_distance(t_info *info, t_ray *r)
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
	if (r->side == 0)
		r->dist = (r->map.x - info->pos.x
				+ (1 - r->step.x) / 2) / r->dir.x;
	else
		r->dist = (r->map.y - info->pos.y
				+ (1 - r->step.y) / 2) / r->dir.y;
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

void	select_texture(t_info *info, t_ray *r)
{
	if (r->side == 0 && r->step.x < 0)
		info->tex_num = 0;
	else if (r->side == 0 && r->step.x > 0)
		info->tex_num = 1;
	else if (r->side == 1 && r->step.y < 0)
		info->tex_num = 2;
	else if (r->side == 1 && r->step.y > 0)
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
	info->tex_pos = (r->draw_start - info->hght / 2 + r->wall_hight / 2)
		* info->step_y;
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
		pixel = info->texture[info->tex_num][TEX_HGHT
			* info->tex.y + info->tex.x];
		info->buf[wall][stripe] = pixel;
		wall++;
	}
	floor = r.draw_end;
	while (floor < info->hght)
		info->buf[floor++][stripe] = info->f_color;
}

void	locate_sprites(t_info *info)
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
			if (info->map[i][j] == 2)
			{
				info->sprt[count].x = i + .5;
				info->sprt[count].y = j + .5;
				count++;
			}
			j++;
		}
		i++;
	}
}

void	calc_sprite_dist(t_info *info)
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

void	arrange_sprites(t_info *info, t_pair *sp)
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

void	calc_sprite_info(t_info *info, t_sprite *s)
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

void	configure_sprite(t_info *info, t_sprite s, int stripe)
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
				s.color = info->texture[4][TEX_WID
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
		configure_sprite(info, s, stripe);
		i++;
	}
}

void	configure_image(t_info *info)
{
	t_ray	r;
	int		stripe;

	stripe = 0;
	while (stripe < info->wid)
	{
		init_ray_information(info, &r, stripe);
		set_ray_distance(info, &r);
		calculate_wall_height(info, &r);
		select_texture(info, &r);
		calculate_texture_stripe(info, &r);
		draw_buffer(info, r, stripe);
		info->sp_buf[stripe] = r.dist;
		stripe++;
	}
	if (info->sp_count > 0)
		draw_sprites(info);
}

void	draw_image(t_info *info)
{
	int	x;
	int	y;

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

int	game_loop(t_info *info)
{
	move_player(info);
	configure_image(info);
	draw_image(info);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_tex *tex)
{
	int	i;
	int	j;

	i = 0;
	tex->img = mlx_xpm_file_to_image(info->mlx, path, &tex->wid, &tex->hght);
	if (!(tex_img))
		free_exit(info, "recheck image paths");
	tex->addr = (int *)
		mlx_get_data_addr(tex->img, &tex->bpp, &tex->len, &tex->end);
	while (i < tex->hght)
	{
		j = 0;
		while (j < tex->wid)
		{
			texture[tex->wid * i + j] = tex->addr[tex->wid * i + j];
			j++;
		}
		i++;
	}
	mlx_destroy_image(info->mlx, tex->img);
}

void	load_textures(t_info *info)
{
	t_tex	tex;

	load_image(info, info->texture[0], info->no_path, &tex);
	load_image(info, info->texture[1], info->so_path, &tex);
	load_image(info, info->texture[2], info->we_path, &tex);
	load_image(info, info->texture[3], info->ea_path, &tex);
	load_image(info, info->texture[4], info->s_path, &tex);
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

void	init_textures(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	info->texture = (int **)malloc(sizeof(int *) * 5);
	if (!(info->texture))
		free_exit(info, "Memory allocation error");
	info->texture_flag++;
	while (i < 5)
	{
		info->texture[i] = (int *)malloc(sizeof(int) * (TEX_HGHT * TEX_WID));
		if (!(info->texture[i]))
			free_exit(info, "Memory allocaiton error");
		info->texture_flag++;
		i++;
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

void	count_col(t_info *info, char *line)
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
	if (fd == -1)
		failed_exit("Could not open .cub file");
	while (is_not_map(line, fd, info))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		check_ret(info, line, fd, ret);
	}
	while (!(is_not_map(line, fd, info)))
	{
		info->row_count++;
		count_col(info, line);
		safe_free(line);
		ret = get_next_line(fd, &line);
		check_ret(info, line, fd, ret);
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
	info->sp_buf = NULL;
	info->sp_dist = NULL;
	info->sp_ordr = NULL;
	info->sprt = NULL;
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

void	init_game(t_info *info)
{
	init_pointers(info);
	info->mlx = mlx_init();
	if (!(info->mlx))
		free_exit(info, "Connection to X-server Failed");
	info->mv_spd = .03;
	info->rot_spd = .03;
	info->map_flag = -1;
	info->buf_flag = -1;
	info->texture_flag = -1;
	info->f_color = -1;
	info->c_color = -1;
	info->wid = 0;
	info->hght = 0;
	info->row_count = 0;
	info->col_count = 0;
	count_map_rows(info);
	parse_cub_info(info);
	init_buf(info);
	init_textures(info);
	load_textures(info);
	init_sprite_info(info);
	init_keys(info);
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

	fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd == -1)
		free_exit(info, "Could not create .bmp file");
	create_bmfh(info, fd);
	create_bmih(info, fd);
	configure_image(info);
	write_rpd(info, fd);
	close(fd);
	successful_exit(info, 1);
}

void	check_arg_count(int argc, char **argv)
{
	if (argc > 3)
		failed_exit("Too many arguments");
	else if (argc < 2)
		failed_exit("Please select which .cub file to read");
	else if (argc == 3 && (ft_memcmp("--save", argv[2], 6) != 0))
		failed_exit("Second argument should be --save");
}

int	main(int argc, char **argv)
{
	t_info	info;

	check_arg_count(argc, argv);
	filename_check(&info, argv[1]);
	init_game(&info);
	if (argc == 3 && (ft_memcmp("--save", argv[2], 6) == 0))
		create_bmp(&info, "cub3D.bmp");
	info.win = mlx_new_window(info.mlx, info.wid, info.hght, "Cub3D");
	if (!(info.win))
		free_exit(&info, "Could not create window");
	info.img.img = mlx_new_image(info.mlx, info.wid, info.hght);
	if (!(info.img.img))
		free_exit(&info, "Could not create image");
	info.img.addr = (int *)mlx_get_data_addr(info.img.img,
			&info.img.bpp, &info.img.len, &info.img.end);
	mlx_loop_hook(info.mlx, game_loop, &info);
	mlx_hook(info.win, 2, 1L << 0, &key_press, &info);
	mlx_hook(info.win, 3, 1L << 1, &key_release, &info);
	mlx_hook(info.win, 33, 1L << 17, &successful_exit, &info);
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
