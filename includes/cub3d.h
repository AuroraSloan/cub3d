/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompso <jthompso@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:32:40 by jthompso          #+#    #+#             */
/*   Updated: 2021/05/09 18:25:52 by jthompso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define ESC 65307
# define UP 65362
# define DWN 65364
# define LFT 65361
# define RT 65363
# define W 119
# define A 97
# define S 115
# define D 100
# define TEX_HGHT 64
# define TEX_WID 64

typedef	struct	s_img
{
	void	*img;
	int	*addr;
	int	bpp;
	int	len;
	int	end;
}		t_img;

typedef	struct	s_tex
{
	void	*img;
	int	*addr;
	int	bpp;
	int	len;
	int	end;
	int	wid;
	int	hght;
}		t_tex;

typedef struct	s_dble_vec
{
	double	x;
	double	y;
}		t_dble_vec;

typedef struct s_int_vec
{
	int x;
	int y;
}		t_int_vec;

typedef struct s_keys
{
	int up;
	int down;
	int left;
	int right;
	int w;
	int a;
	int s;
	int d;
}		t_keys;

typedef	struct	s_info
{
	void		*mlx;
	void		*win;
	char		*name;
	int		wid;
	int		hght;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*s_path;
//	char		*f_path;
//	char		*c_path;
	int		f_color;
	int		c_color;
	int		**map;
	int		map_flag;
	int		col;
	int		col_count;
	int		row;
	int		row_count;	
	t_img		img;	
	char		start;
	t_dble_vec	pos;
	t_dble_vec	dir;
	t_dble_vec	cam;
	double		mv_spd;
	double		rot_spd;
	double		old_dir;
	double		old_cam;
	int		tex_num;
	double		wall_x;
	t_int_vec	tex;
	double		step_y;
	double		tex_pos;
	int		**buf;
	int		buf_flag;
	int		**texture;
	int		texture_flag;
	t_keys		key;
}		t_info;

typedef struct	s_ray
{
	double		cam_x;
	t_dble_vec	dir;
	t_int_vec	map;
	t_dble_vec	side_dist;
	t_dble_vec	delta_dist;
	t_dble_vec	step;
	double		dist;
	int		hit;
	int		side;
	int		wall_hight;
	int		draw_start;
	int		draw_end;
	int		color;
	t_dble_vec	floor_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	t_dble_vec	current_floor;
	t_int_vec	floor_tex;
	int		pat;
	int		f_tex;
}			t_ray;
#endif
