/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bderya <bderya@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:46:02 by yogun             #+#    #+#             */
/*   Updated: 2023/01/30 12:21:39 by bderya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define HEIGHT   1000
# define WIDTH    1000
# define KEYS     '0'

# include "./src/libft/libft.h"
# include "mlx/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdbool.h>

/*
	depth:	Depth of field
	ra:		Ray angle
	zeros:	Number of zeros
	zerosh:	Number of zeros in horizontal
	atan_ra:	Atan of ray angle
	hx:		Horizontal X
	hy:		Horizontal Y
	vx:		Vertical X
	vy:		Vertical Y
	rx:		Ray X first hit x axis
	ry:		Ray Y first hit y axis
	xo:	    X offset
	yo:		Y offset
*/
typedef struct s_ray {
	int		depth;
	double	xo;
	double	yo;
	double	ra;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	px;
	double	py;
	double	rx;
	double	ry;
	int		zeros;
	int		zerosh;
	double	atan_ra;
	double	tan_ra;
}				t_ray;

typedef struct s_sprite {
	double	x;
	double	y;
	double	z;
	double	sin;
	double	cos;
}				t_sprite;

/*
	mlx: 	A pointer to the connection to the correct graphical system which was
			which holds the location of our current MLX instance.
	*win: 	A pointer to the window we have just created for game 
	pa :	Player Angle
	no: 	North
	so:		South
	ea:		East
	we:		West
	px: 	X position of player
	py:		Y position of player
	pdx:	In X axis tilt value of the player
	pdy:	In Y axis tilt value of the player
	d_x:	Door X position
	d_y: 	Door Y position
	step_num:	Number of steps
	is_open:	Door is open or not
	sprite:	Is there a sprite or not
	key_px:	Key X position
	key_py:	Key Y position
	spr_scale:	Sprite scale
	t_x:	Translation X
	t_y:	Translation Y
	sx: 	Distance from sprite x axis
	sx: 	Distance from sprite y axis
	stepy: 	Step in Y axis
	b:      Some const
	lineh: 	Line height
	linelen:	Line length
	t_x_step:	Translation X step
	t_y_step:	Translation Y step
*/
typedef struct s_dB {
	void	*mlx;
	void	*win;
	void	*img;
	void	*no;
	void	*so;
	void	*ea;
	void	*we;
	void	*minimap;
	void	*key;
	void	*key2;
	void	*door;
	char	*addr[9];
	int		bits_per_pixel[9];
	int		line_length[9];
	int		endian[9];
	int		c[3];
	int		f[3];
	char	*line;
	char	player;
	double	map_width;
	double	map_height;
	int		mouse_x;
	int		mouse_y;
	char	mouse;
	double	px;
	double	py;
	double	pdx;
	double	pdy;
	double	pa;
	double	dist;
	int		zeros;
	int		ray;
	double	stepy;
	int		linelen;
	char	is_key;
	int		d_x;
	int		d_y;
	int		step_num;
	char	is_open;
	char	sprite;
	double	key_px;
	double	key_py;
	double	spr_scale;
	double	t_x;
	double	t_y;
	double	t_x_step;
	double	t_y_step;
	double	b;
	double	sy;
	double	sx;
	double	angle;
	int		loop;
	char	sprite_state;
	t_list	*map;
}				t_dB;

void	ft_error(char *s, t_dB *db);
void	ft_free(t_dB *db);
int		ft_exit_game(t_dB *db);
void	ft_lstfree(t_list *map);

void	ft_map_process(t_dB *db, char *argv);
void	ft_map_translate(t_dB *db, char *line, int fd);
void	ft_map_control(t_list	*tmp, t_dB *db);
void	ft_map_init(char *line, t_dB *db, int fd);
void	ft_initdata(t_dB *db);
void	ft_minimap_render(t_list *map, t_dB *db);
void	my_mlx_pixel_put_mini(t_dB *db, int x, int y, int color);
void	init_sprite(t_dB *db);
void	sprite_draw(t_dB *db, int i);
int		ft_game_start(t_dB *db);
void	ft_game_render(t_dB *db);
int		ft_key_pressed(int keycode, t_dB *db);
void	ft_ray_cast(t_dB *db, t_ray *ray);
void	ft_vertical_ray(t_dB *db, t_ray *ray);
void	line_draw(t_dB *db, int i);
char	get_map_char(int mx, int my, t_dB *db);
void	put_map_char(int mx, int my, t_dB *db, char c);
void	my_mlx_pixel_put(t_dB *db, int x, int y, int color);
double	calculate_distance(t_ray *ray);
double	ft_degree_to_radian(double db);
double	angle_to_360(double db);
void	left_key(t_dB *db);
void	right_key(t_dB *db);
void	key_e(t_dB *db);
void	ft_timer(t_dB *db);
int		ft_check_map_format(char *str, char *s2);
void	ft_error(char *str, t_dB *db);
void	ft_free(t_dB *db);
void	ft_start(char *argv);

#endif