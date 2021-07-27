#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <unistd.h>

void	free_exit(t_info *info, char *exit_status)
{
	free_memory(info);
	ft_failed_exit(exit_status, NULL);
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
