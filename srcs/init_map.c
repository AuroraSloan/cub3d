#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <unistd.h>

static void	set_start(t_info *info, char start, int fd, char *line)
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

static void	init_map_row(t_info *info, int fd, char *line)
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
		if (line[info->col] == '2' || line[info->col] == '3'
			|| line[info->col] == '4')
			info->sp_count++;
		if (is_start(line[info->col]))
			set_start(info, line[info->col], fd, line);
		else if (line[info->col] == ' ')
			info->map[info->row][info->col] = 0;
		else
			info->map[info->row][info->col] = line[info->col] - '0';
		if (info->map[info->row][info->col] > 4)
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
