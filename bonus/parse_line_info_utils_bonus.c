/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  parse_line_info_utils_bonus.c                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/14 13:50:39 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/21 19:09:55 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"
#include "../libraries/libft/libft.h"

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

void	init_ea_s_f_paths(t_info *info, char *line, int fd)
{
	if (ft_memcmp(line, "EA", 2) == 0)
	{
		if (info->ea_path != NULL)
			free_line(info, fd, line, "Mulptiple EA path info");
		info->ea_path = ft_strtrim(&line[2], " ");
		if (!(info->ea_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (ft_memcmp(line, "S ", 2) == 0)
	{
		if (info->s_path != NULL)
			free_line(info, fd, line, "Mulptiple S path info");
		info->s_path = ft_strtrim(&line[1], " ");
		if (!(info->s_path))
			free_line(info, fd, line, "can't allocate");
	}
	else if (ft_memcmp(line, "F ", 2) == 0)
	{
		if (info->f_path != NULL)
			free_line(info, fd, line, "Mulptiple F path info");
		info->f_path = ft_strtrim(&line[1], " ");
		if (!(info->f_path))
			free_line(info, fd, line, "can't allocate");
	}
}
