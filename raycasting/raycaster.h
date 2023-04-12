/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:14:51 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/12 18:30:23 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>

# define PI 3.141592653589793
# define ALPHA 1.0471975512
# define X_RES 2000
# define Y_RES 1000
# define SLOPE 0
# define B 1
# define V 1
# define H 0
# define DIV 64
# ifdef __linux__
#  include "../mlx_linux/mlx.h"
#  define W 119
#  define S 115
#  define D 100
#  define A 97
#  define UP 65362
#  define RIGHT 65363
#  define DOWN 65364
#  define LEFT 65361
#  define ESC 65307   
# else
#  include "../mlx/mlx.h"
#  define W 13
#  define S 1
#  define D 2
#  define A 0
#  define UP 126
#  define RIGHT 124
#  define DOWN 125
#  define LEFT 123
#  define ESC 53
# endif

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_line
{
	double	x_coef;
	double	offset;
}	t_line;

typedef struct s_ray
{
	double	size;
	double	p_size;
	char	*face;
	t_point	dir;
	t_point	start;
	t_point	end;
}	t_ray;

typedef struct s_pixel
{
	int		x;
	int		y;
}	t_pixel;

typedef struct s_camera
{
	t_point	dir;
	t_point	start;
	t_point	end;
	double	size;
	double	dist;
}	t_camera;

typedef struct s_player
{
	t_point		pos;
	t_camera	cam;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*path;
	int		width;
	int		height;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_arg
{
	char			**map;
	t_player		player;
	void			*mlx;
	void			*mlx_win;
	t_ray			*rays;
	t_img			*frame;
	unsigned int	roof_color;
	unsigned int	ground_color;
	int				vertical_vector;
	int				horizontal_vector;
	int				moment_vector;
	t_img			no;
	t_img			so;
	t_img			ea;
	t_img			we;
}	t_arg;

void			rays_gen(t_player *player, t_ray rays[X_RES]);
t_point			goto_next_edge(t_point start, t_ray *ray);
void			window(char **map, t_player player, t_ray rays[X_RES]);
int				in_wall(t_point pos, char **map);
void			ray_len(t_point start, t_ray *ray, char **map);
void			find_perpendicular_len(t_arg *arg, t_ray *ray);
void			turn(t_arg *arg, double rad, int moment);
void			put_walls(t_arg *arg, t_ray *rays);
void			move(t_arg *arg, double speed, int x, int y);
int				pressed(int keycode, t_arg *arg);
int				unpressed(int keycode, t_arg *arg);
int				unfocused(int keycode, t_arg *arg);
int				ft_exit_success(t_arg *arg);
void			arg_walls_init(t_arg *arg);
void			set_dir(t_player *player, char dir);
unsigned int	color_from_texture(t_img *texture, int x, int y);
#endif