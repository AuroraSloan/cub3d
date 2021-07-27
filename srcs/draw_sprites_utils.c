#include "../includes/cub3d.h"

void	init_sptext_info(t_info *info, int i, int j, int count)
{
	if (info->map[i][j] == 2)
		info->sp_tex[count] = 4;
	else if (info->map[i][j] == 3)
		info->sp_tex[count] = 6;
	else if (info->map[i][j] == 4)
		info->sp_tex[count] = 7;
}
