/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/25 12:41:27 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#define X_RES 480

typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

typedef struct s_line
{
	float	x_coef;
	float	offset;
}	t_line;

typedef struct s_ray
{
	float	size;
	t_point	dir;
}	t_ray;

typedef struct s_camera
{
	t_point	dir;
	t_point	start;
	float	size;
}	t_camera;

typedef struct s_player
{
	t_point		pos;
	t_camera	cam;
}	t_player;

void	rays_gen(t_player *player, t_ray rays[X_RES])
{
	t_point	ray_incr;
	int		i;
	t_point	cam_dir;
	float	cam_dir_norm;
	float	y;
	float	x;

	ray_incr.x = (fabs(player->cam.dir.x - player->cam.start.x) * 2) / (X_RES - 1);
	ray_incr.y = (fabs(player->cam.dir.y - player->cam.start.y) * 2) / (X_RES - 1);
	i = -1;
	cam_dir.x = player->cam.dir.x - player->cam.start.x;
	cam_dir.y = player->cam.dir.y - player->cam.start.y;
	cam_dir_norm = sqrtf(powf(cam_dir.x, 2) + powf(cam_dir.y, 2));
	cam_dir.x = cam_dir.x / cam_dir_norm;
	cam_dir.y = cam_dir.y / cam_dir_norm;
	printf(">_ %f %f\n", cam_dir.x, cam_dir.y);
	while (++i < X_RES)
	{
		x = player->cam.start.x + ((ray_incr.x * i) * (cam_dir.x));
		y = player->cam.start.y + ((ray_incr.y * i) * (cam_dir.y));
		rays[i].dir.x = x - player->pos.x;
		rays[i].dir.y = y - player->pos.y;
	}
}

int	in_wall(t_point pos, int **map)
{
	if (map[(int)pos.y, (int)pos.x])
		return (1);
	return (0);
}

t_point goto_next_edge(t_point pos)
{
	t_point	res;
	
	return res;
}

void	rays_len(t_player player, t_ray rays, int **map)
{
	int	i;
	t_point	pos;

	i = -1;
	while (++i < X_RES)
	{
		pos = rays.dir;
		while (!in_wall(pos, map))
		{
			pos = goto_next_edge(pos);
		}
	}
}

int	main()
{
	t_ray 		rays[X_RES];
	t_player	player;
	int	tab[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 53, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 64, 0, 0, 0},
		{1, 0, 0, 0, 0, 2, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	player.pos.x = 5;
	player.pos.y = 5;
	player.cam.size= 2;
	player.cam.dir.x = 5;
	player.cam.dir.y = 4;
	player.cam.start.x = 4;
	player.cam.start.y = 4;
	rays_gen(&player, rays);
	printf("%d\n", tab[5][5]);
}

