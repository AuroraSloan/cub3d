#include "../includes/cub3d.h"
#include <math.h>

void	turn_left(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(info->rot_spd) - info->dir.y * sin(info->rot_spd);
	info->dir.y = old_dir * sin(info->rot_spd) + info->dir.y * cos(info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(info->rot_spd) - info->cam.y * sin(info->rot_spd);
	info->cam.y = old_cam * sin(info->rot_spd) + info->cam.y * cos(info->rot_spd);
}

void	turn_right(t_info *info)
{
	double	old_dir;
	double	old_cam;

	old_dir = info->dir.x;
	info->dir.x = info->dir.x * cos(-info->rot_spd) - info->dir.y * sin(-info->rot_spd);
	info->dir.y = old_dir * sin(-info->rot_spd) + info->dir.y * cos(-info->rot_spd);
	old_cam = info->cam.x;
	info->cam.x = info->cam.x * cos(-info->rot_spd) - info->cam.y * sin(-info->rot_spd);
	info->cam.y = old_cam * sin(-info->rot_spd) + info->cam.y * cos(-info->rot_spd);
}

static void	move(t_info *info)
{
	if (info->key.w)
	{
		if (!info->map[(int)(info->pos.x + info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x += info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y + info->dir.y * info->mv_spd)])
			info->pos.y += info->dir.y * info->mv_spd;
	}
	if (info->key.s)
	{
		if (!info->map[(int)(info->pos.x - info->dir.x * info->mv_spd)][(int)(info->pos.y)])
			info->pos.x -= info->dir.x * info->mv_spd;
		if (!info->map[(int)(info->pos.x)][(int)(info->pos.y - info->dir.y * info->mv_spd)])
			info->pos.y -= info->dir.y * info->mv_spd;
	}
    if (info->key.a)
    {
        if (!info->map[(int)(info->pos.x - info->cam.x * info->mv_spd)][(int)(info->pos.y)])
            info->pos.x -= info->cam.x * info->mv_spd;
        if (!info->map[(int)(info->pos.x)][(int)(info->pos.y - info->cam.y * info->mv_spd)])
            info->pos.y -= info->cam.y * info->mv_spd;
    }
    if (info->key.d)
    {
        if (!info->map[(int)(info->pos.x + info->cam.x * info->mv_spd)][(int)(info->pos.y)])
            info->pos.x += info->cam.x * info->mv_spd;
        if (!info->map[(int)(info->pos.x)][(int)(info->pos.y + info->cam.y * info->mv_spd)])
            info->pos.y += info->cam.y * info->mv_spd;
    }
}

void	move_player(t_info *info)
{
	if (info->key.left || (info->exit && info->mouse.x < info->old_mouse.x))
		turn_left(info);
	if (info->key.right || (info->exit && info->mouse.x > info->old_mouse.x))
		turn_right(info);
	move(info);
}
