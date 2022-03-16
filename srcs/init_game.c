#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
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
	info->f_path = NULL;
	info->sp_buf = NULL;
	info->sp_dist = NULL;
	info->sp_ordr = NULL;
	info->sprt = NULL;
	info->sp_tex = NULL;
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
	info->sp_buf = malloc(sizeof(double) * info->wid);
	info->sp_dist = malloc(sizeof(double) * info->sp_count);
	info->sp_ordr = malloc(sizeof(int) * info->sp_count);
	info->sprt = malloc(sizeof(t_d_vec) * info->sp_count);
	info->sp_tex = malloc(sizeof(int) * info->sp_count);
	if (!info->sp_buf || !info->sp_dist || !info->sp_ordr || !info->sprt || !info->sp_tex)
		free_exit(info, "Memory allocation error");
    ft_bzero(info->sp_buf, sizeof(double) * info->wid);
    ft_bzero(info->sp_dist, sizeof(double) * info->sp_count);
    ft_bzero(info->sp_ordr, sizeof(int) * info->sp_count);
    ft_bzero(info->sprt, sizeof(t_d_vec) * info->sp_count);
    ft_bzero(info->sp_tex, sizeof(int) * info->sp_count);
}

void	init_buf(t_info *info)
{
	int	i;

	i = 0;
	info->buf = malloc(sizeof(int *) * info->hght);
	if (!(info->buf))
		free_exit(info, "Memory allocation error");
	info->buf_flag++;
	while (i < info->hght)
	{
		info->buf[i] = malloc(sizeof(int) * info->wid);
		if (!(info->buf[i]))
			free_exit(info, "Memory allocation error");
        ft_bzero(info->buf[i], info->wid * sizeof(int));
		info->buf_flag++;
		i++;
	}
}

static void	count_col(t_info *info, char *line)
{
	size_t  len;

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
	while (!is_map_row(line, fd, info))
	{
		if (line != NULL)
			safe_free(line);
		ret = get_next_line(fd, &line);
		check_failed_ret(info, line, fd, ret);
	}
	while (is_map_row(line, fd, info))
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
