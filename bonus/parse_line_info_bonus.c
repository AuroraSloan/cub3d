/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  parse_line_info_bonus.c                              :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/13 21:55:06 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/17 20:19:20 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../libraries/libft/libft.h"

static void	init_paths(t_info *info, char *line, int fd)
{
	if (ft_memcmp(line, "NO", 2) == 0)
	{
		if (info->no_path != NULL)
			free_line(info, fd, line, "Mulptiple no_path info");
		info->no_path = ft_strtrim(&line[2], " ");
		if (!(info->no_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (ft_memcmp(line, "SO", 2) == 0)
	{
		if (info->so_path != NULL)
			free_line(info, fd, line, "Mulptiple SO path info");
		info->so_path = ft_strtrim(&line[2], " ");
		if (!(info->so_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (ft_memcmp(line, "WE", 2) == 0)
	{
		if (info->we_path != NULL)
			free_line(info, fd, line, "Mulptiple WE path info");
		info->we_path = ft_strtrim(&line[2], " ");
		if (!(info->we_path))
			free_line(info, fd, line, "can't allocate");
	}
	init_ea_s_paths(info, line, fd);
}

static int	init_c_f_color(t_info *info, char *line, int fd)
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

static void	init_resolution(t_info *info, char *line, int fd)
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
		free_line(info, fd, line, "Res must be two #s greater 0");
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
