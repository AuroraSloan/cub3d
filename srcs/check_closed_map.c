#include "../includes/cub3d.h"
#include "../libraries/libft/libft.h"
#include <stdlib.h>

static void	free_tmp_map(t_info *info, int **tmp_map, int cnt, char *error)
{
	int	i;

	i = 0;
	while (i < cnt)
		safe_free(tmp_map[i++]);
	safe_free(tmp_map);
	if (error)
		free_exit(info, error);
}

static void	floodfill(t_info *info, int **tmp_map, size_t x, size_t y)
{
    if ((x == 0 || x >= info->row_count - 1 || y == 0 || y >= info->col_count - 1) && tmp_map[x][y] != WALL)
        free_tmp_map(info, tmp_map, (int)info->row_count, "map not closed");
    if (tmp_map[x][y] != WALL && tmp_map[x][y] != FILL)
    {
        tmp_map[x][y] = FILL;
        floodfill(info, tmp_map, x - 1, y);
        floodfill(info, tmp_map, x + 1, y);
        floodfill(info, tmp_map, x, y - 1);
        floodfill(info, tmp_map, x, y + 1);
    }
}

static int	**init_tmp_map(t_info *info)
{
	int **tmp_map;
	int cnt;

	cnt = 0;
	tmp_map = malloc(sizeof(int *) * (int)info->row_count);
	if (!(tmp_map))
		free_exit(info, "Memory allocation error");
	while (cnt < (int)info->row_count)
	{
		tmp_map[cnt] = malloc(sizeof(int) * (int)info->col_count);
		if (!(tmp_map[cnt]))
			free_tmp_map(info, tmp_map, cnt, "Can't allocate mem");
		cnt++;
	}
	return (tmp_map);
}

void	check_closed_map(t_info *info, int x, int y)
{
	int	**tmp_map;
	size_t  i;

	tmp_map = init_tmp_map(info);
	i = 0;
	while (i < info->row_count)
	{
        ft_memcpy(tmp_map[i], info->map[i], sizeof(int) * (int)info->col_count);
		i++;
	}
	floodfill(info, tmp_map, x, y);
	free_tmp_map(info, tmp_map, (int)info->row_count, NULL);
}
