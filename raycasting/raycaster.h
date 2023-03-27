/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:14:51 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/27 20:25:46 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define X_RES 1000
# define Y_RES 1000

#  include "mlx_linux/mlx.h"
#  define W 119
#  define S 115
#  define D 100
#  define A 97
#  define UP 65362
#  define RIGHT 65363
#  define DOWN 65364
#  define LEFT 65361
#  define ESC 65307  
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
	t_point	dir;
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
	double	size;
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
	int			**map;
	t_player	player;
	void		*mlx;
	void		*mlx_win;
	t_ray 		*rays;
	t_img		*frame;
}	t_arg;

void	rays_gen(t_player *player, t_ray rays[X_RES]);
void	rays_len(t_player *player, t_ray rays[X_RES], int **map);
void	window(int **map, t_player player, t_ray rays[X_RES]);
int		in_wall(t_point pos, int **map);

#endif