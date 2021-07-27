#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

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

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bpp;
	int		len;
	int		end;
}				t_img;

typedef struct s_tex
{
	void	*img;
	int		*addr;
	int		bpp;
	int		len;
	int		end;
	int		wid;
	int		hght;
}				t_tex;

typedef struct s_d_vec
{
	double	x;
	double	y;
}				t_d_vec;

typedef struct s_i_vec
{
	int	x;
	int	y;
}				t_i_vec;

typedef struct s_arrange
{
	double	a;
	int		b;
	int		c;
}				t_arrange;

typedef struct s_keys
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	w;
	int	a;
	int	s;
	int	d;
}				t_keys;
typedef struct s_mini_map
{
	int	map_i;
	int	map_j;
	int	mm_i;
	int	mm_j;
	int	mm_wid;
	int	mm_hght;
	int	wid_cnt;
	int	hght_cnt;
}				t_mini_map;

typedef struct s_info
{
	void	*mlx;
	void	*win;
	char	*name;
	int		wid;
	int		hght;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*s_path;
	char	*f_path;
	int		c_color;
	int		**map;
	int		map_flag;
	int		col;
	int		col_count;
	int		row;
	int		row_count;	
	int		save;
	t_img	img;	
	char	start;
	t_d_vec	pos;
	t_d_vec	dir;
	t_d_vec	cam;
	double	mv_spd;
	double	rot_spd;
	int		tex_num;
	double	wall_x;
	t_i_vec	tex;
	double	step_y;
	double	tex_pos;
	int		**buf;
	int		buf_flag;
	int		**texture;
	int		texture_flag;
	t_keys	key;
	double	*sp_buf;
	int		sp_count;
	double	*sp_dist;
	int		*sp_ordr;
	t_d_vec	*sprt;
	int		bmp;
	int		*sp_tex;
	t_i_vec	mouse;
	t_i_vec	old_mouse;
	int		mini_map;
	int		cucco;
	int		exit;
}					t_info;

typedef struct s_ray
{
	double	cam_x;
	t_d_vec	dir;
	t_i_vec	map;
	t_d_vec	side_dist;
	t_d_vec	delta_dist;
	t_i_vec	step;
	double	dist;
	int		hit;
	int		side;
	int		wall_hight;
	int		draw_start;
	int		draw_end;
	t_d_vec		floor_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	t_d_vec		current_floor;
	t_i_vec		floor_tex;
	int		pat;
	int		f_tex;
	
}				t_ray;

typedef struct s_sprite
{
	t_d_vec	loc;
	double	inv_det;
	t_d_vec	mod;
	int		screen;
	int		mv_screen;
	int		hght;
	t_i_vec	draw_start;
	t_i_vec	draw_end;
	int		wid;
	t_i_vec	tex;
	int		col;
	int		d;
	int		color;
}				t_sprite;

void	safe_free(void *ptr);
void	free_memory(t_info *info);
void	failed_exit(char *exit_status);
void	free_exit(t_info *info, char *exit_status);
void	free_line(t_info *info, int fd, char *line, char *exit_status);
void	check_failed_ret(t_info *info, char *line, int fd, int ret);
void	check_failed_fd(t_info *info, int fd);
void	create_bmp(t_info *info, char *file_name);
void	init_pointers_keys(t_info *info);
void	init_sprite_info(t_info *info);
void	init_buf(t_info *info);
void	count_map_rows(t_info *info);
void	init_textures(t_info *info);
int		is_not_map(char *line, int fd, t_info *info);
void	parse_cub_info(t_info *info);
int		create_rgb(int r, int g, int b);
int		find_next_color(t_info *info, int fd, char *line, int i);
int		find_first_color(t_info *info, int fd, char *line);
void	init_ea_s_f_paths(t_info *info, char *line, int fd);
int		is_start(char start);
void	init_n_s_vectors(t_info *info);
void	init_w_e_vectors(t_info *info);
void	init_map(int ret, t_info *info, int fd, char *line);
int		is_valid_game_info(char *line);
void	parse_line_info(t_info *info, int fd, char *line);
void	check_closed_map(t_info *info, int x, int y);
void	move_player(t_info *info);
int		successful_exit(t_info *info);
int		key_press(int keycode, t_info *info);
int		key_release(int keycode, t_info *info);
void	draw_image(t_info *info);
void	configure_image(t_info *info);
void	select_texture(t_info *info, t_ray *r);
void	init_ray_information(t_info *info, t_ray *r, int stripe);
void	calculate_ray_distance(t_info *info, t_ray *r);
void	draw_sprites(t_info *info);
void	sort_sprites(t_info *info);
int	mouse_movement(int x, int y, t_info *info);
void	turn_left(t_info *info);
void	turn_right(t_info *info);
int	mouse_enter(t_info *info);
int	mouse_exit(t_info *info);
void	calc_floor_wall(t_info *info, t_ray *r);
void	draw_floor(t_info *info, t_ray *r, int stripe);
void	init_sptext_info(t_info *info, int i, int j, int count);
void	check_mini_map(t_info *info);
void	draw_mini_map(t_info *info);
void	manage_items(t_info *info);

#endif
