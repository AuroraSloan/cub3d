#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <fcntl.h>

# ifdef __linux__
# include "../libraries/minilibx-linux/mlx.h"

static void	compare_resolution(t_info *info)
{
	int	screen_width;
	int	screen_hight;

	mlx_get_screen_size(info->mlx, &screen_width, &screen_hight);
	if (info->wid > screen_width)
		info->wid = screen_width;
	if (info->hght > screen_hight)
		info->hght = screen_hight;
}
#endif

static void	cub_info_check(t_info *info, int fd, char *line)
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
	if (!info->f_path)
		free_line(info, fd, line, "Check F path info or map location");
	if (info->c_color == -1)
		free_line(info, fd, line, "Check C color info or map location");
}

bool    is_valid_game_info(char *line)
{
    return (ft_memcmp(&line[0], "R ", 2) == 0
        || ft_memcmp(&line[0], "NO", 2) == 0
        || ft_memcmp(&line[0], "SO", 2) == 0
        || ft_memcmp(&line[0], "WE", 2) == 0
        || ft_memcmp(&line[0], "EA", 2) == 0
        || ft_memcmp(&line[0], "S ", 2) == 0
        || ft_memcmp(&line[0], "F ", 2) == 0
        || ft_memcmp(&line[0], "C ", 2) == 0);
}

static bool is_valid_map_info(char c)
{
    return (c == '1' || c == '0' || c == ' ');
}

bool    is_map_row(char *line, int fd, t_info *info)
{
    if (line == NULL || line[0] == '\0')
		return (false);
	if (is_valid_map_info(line[0]))
		return (true);
	if (!is_valid_game_info(line) && !is_valid_map_info(line[0]))
		free_line(info, fd, line, "invalid character in .cub file");
	return (false);
}

void	parse_cub_info(t_info *info)
{
	char	*line;
	int		fd;
	int		ret;

	line = NULL;
	if (info->row_count > 100 || info->col_count > 100)
		free_exit(info, "Please reduce size of map");
	fd = open(info->name, O_RDONLY);
	check_failed_fd(info, fd);
	while (!is_map_row(line, fd, info))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		check_failed_ret(info, line, fd, ret);
		parse_line_info(info, fd, line);
	}	
	cub_info_check(info, fd, line);
    # ifdef __linux__
	if (!info->save)
		compare_resolution(info);
    #endif
	init_map(ret, info, fd, line);
	check_closed_map(info, (int)info->pos.x, (int)info->pos.y);
}
