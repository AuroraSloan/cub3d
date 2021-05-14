/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*  failed_exit.c                                        :+:      :+:    :+:  */
/*                                                     +:+ +:+         +:+    */
/*  By: jthompso <jthompso@student.42tokyo.jp>       +#+  +:+       +#+       */
/*                                                 +#+#+#+#+#+   +#+          */
/*  Created: 2021/05/13 20:52:32 by jthompso            #+#    #+#            */
/*  Updated: 2021/05/13 20:59:16 by jthompso           ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <unistd.h>

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

void	check_failed_ret(t_info *info, char *line, int fd, int ret)
{
	if (ret == 0)
		free_line(info, fd, line, "check map info");
	if (ret == -1)
		free_line(info, fd, line, "memory error");
}

void	check_failed_fd(t_info *info, int fd)
{
	if (fd == -1)
		free_exit(info, "Could not open .cub file");
}
