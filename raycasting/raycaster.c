/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/01 03:04:24 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	rays_gen(t_player *player, t_ray rays[X_RES])
{
	t_point	ray_incr;
	int		i;
	t_point	cam_dir;
	t_point	cam_end;
	t_point	cam_start;
	double	cam_dir_norm;
	double	ray_norm;
	double	y;
	double	x;
	double	slope;

	cam_dir.x = player->cam.end.x - player->cam.start.x;
	cam_dir.y = player->cam.end.y - player->cam.start.y;
	cam_dir_norm = sqrtf(pow(cam_dir.x, 2) + pow(cam_dir.y, 2));
	cam_dir.x = (cam_dir.x / cam_dir_norm);
	cam_dir.y = (cam_dir.y / cam_dir_norm);
	slope = cam_dir.y / cam_dir.x;
	ray_incr.x = fabs((player->cam.end.x - player->cam.start.x)) / ((X_RES) - 1);
	ray_incr.y = fabs((player->cam.end.y - player->cam.start.y)) / ((X_RES) - 1);
	// printf("ray gen >incr %f %f\n", ray_incr.x, ray_incr.y);
	// printf("ray  gen :cam %d norm %f\n", i, cam_dir_norm);
	// printf("ray gen :cam dir %f %f\n", cam_dir.x, cam_dir.y);
	i = -1;
	x = player->cam.start.x;
	y = player->cam.start.y;

	while (++i < X_RES)
	{
		x += ((ray_incr.x) * (cam_dir.x));
		y += ((ray_incr.y) * (cam_dir.y));
		rays[i].dir.x = x - player->pos.x;
		rays[i].dir.y = y - player->pos.y;
		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
		rays[i].dir.x = rays[i].dir.x / ray_norm;
		rays[i].dir.y = rays[i].dir.y / ray_norm;
	}
}

// void	rays_gen(t_player *player, t_ray rays[X_RES])
// {
// 	double	fov_incr;
// 	double	csin;
// 	double	ccos;
// 	int		i;
// 	int		j;
// 	t_point	cam_dir;
// 	t_point	rel_ray;
// 	t_point	rel_ray_prev;
// 	t_point	cam_start;
// 	double	cam_dir_norm;
// 	double	ray_norm;
// 	double	y;
// 	double	x;
// 	double	slope;

// 	fov_incr = player->cam.fov / (X_RES - 1);
// 	i = -1;
// 	while (++i < X_RES / 2)
// 	{
// 		ccos = cos(player->cam.theta - (fov_incr * i));
// 		csin = sin(player->cam.theta - (fov_incr * i));
// 		rel_ray_prev.x = player->cam.dir.x - player->pos.x;
// 		rel_ray_prev.y = player->cam.dir.y - player->pos.y;
// 		rel_ray.x = rel_ray_prev.x * ccos + rel_ray_prev.y * csin; 
// 		rel_ray.y = -rel_ray_prev.x * csin + rel_ray_prev.y * ccos;
// 		rays[i].dir.x = rel_ray.x + player->pos.x;
// 		rays[i].dir.y = rel_ray.y + player->pos.y;
// 		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
// 		rays[i].dir.x = rays[i].dir.x / ray_norm;
// 		rays[i].dir.y = rays[i].dir.y / ray_norm;
// 	}
// 	i -= 1;
// 	j = 0;
// 	while (++i < X_RES)
// 	{
// 		ccos = cos(player->cam.theta + (fov_incr * j));
// 		csin = sin(player->cam.theta + (fov_incr * j));
// 		rel_ray_prev.x = player->cam.dir.x - player->pos.x;
// 		rel_ray_prev.y = player->cam.dir.y - player->pos.y;
// 		rel_ray.x = rel_ray_prev.x * ccos + rel_ray_prev.y * csin; 
// 		rel_ray.y = -rel_ray_prev.x * csin + rel_ray_prev.y * ccos;
// 		rays[i].dir.x = rel_ray.x + player->pos.x;
// 		rays[i].dir.y = rel_ray.y + player->pos.y;
// 		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
// 		rays[i].dir.x = rays[i].dir.x / ray_norm;
// 		rays[i].dir.y = rays[i].dir.y / ray_norm;
// 		j++;
// 	}
// 	printf("x = %f y = %f\n", rays[799].dir.x, rays[799].dir.y);
// }

int	in_wall(t_point pos, int **map)
{
	if (!(pos.x < X_RES && pos.x >= 0 && pos.y < Y_RES && pos.y >= 0) || map[(int)pos.y / 64][(int)pos.x / 64])
		return (1);
	return (0);
}

static t_point	goto_next_edge(t_point pos, t_ray *ray)
{
	t_point	res;

	res = pos;
	while ((int)res.x == (int)pos.x && (int)res.y == (int)pos.y)
	{
		res.x += ray->dir.x;
		res.y += ray->dir.y;
	}
	// res.x = res.x;
	// res.y = res.y;
	return (res);
}

void	ray_len(t_point start, t_ray *ray, int **map)
{		
		t_point	ray_pos;

		ray_pos = start;
		while (!in_wall(ray_pos, map))
			ray_pos = goto_next_edge(ray_pos, (ray));
		ray->start.x = start.x;
		ray->start.y = start.y;
		ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
		ray->end.x = ray_pos.x;
		ray->end.y = ray_pos.y;
		// printf("ray len :raydir =  %f %f raystart = %f %f rayend.x = %f .y = %f\n", ray->dir.x, ray->dir.y, ray->start.x, ray->start.y, ray_pos.x, ray_pos.y);
}

void	rays_len(t_player *player, t_ray rays[X_RES], int **map)
{
	int	i;
	t_point	ray_pos;

	i = -1;
	while (++i < X_RES)
	{
		ray_len(player->pos, &(rays[i]), map);
	}
}

int	main()
{
	t_ray 		rays[X_RES];
	t_player	player;
	int			i;
	int			j;
	int			val;
	int 		*sub;
	int 		**map;
	
	map = (int **)malloc(sizeof(int *) * Y_RES / 64);
	i = -1;
	while(++i < Y_RES / 64)
	{
		sub = (int *)malloc(sizeof(int) * X_RES / 64);
		j = -1;
		while (++j < X_RES / 64)
		{
			val = 0;
			if (i == 0 || j == 0 || i == (Y_RES / 64) - 1|| j == (X_RES / 64) - 1 /*|| i == 400 || j == 400 || i == 600 || j == 600*/)
				val = 1;
			sub[j] = val;
		}
		map[i] = sub;
	}
	player.pos.x = X_RES / 2 ;
	player.pos.y = Y_RES / 2;
	player.cam.size = 5;
	player.cam.dir.x = player.pos.x ;
	player.cam.dir.y = player.pos.y - 10;
	player.cam.start.x = player.cam.dir.x - player.cam.size / 2;
	player.cam.start.y = player.cam.dir.y;
	player.cam.end.x = player.cam.dir.x + player.cam.size / 2;
	player.cam.end.y = player.cam.dir.y;
	// player.cam.fov = PI / 6;
	// player.cam.theta = (3 * PI) / 2;
	printf("cam end y %f\n", player.cam.end.y);
	rays_gen(&player, rays);
	printf("cam end y %f\n", player.cam.end.y);
	// i = -1;
	// while (++i < X_RES)
	// 	printf("%d : %f %f \n", i, rays[i].dir.x, rays[i].dir.y);
	// rays_len(&player, rays, map);
	// while (++i < X_RES)
	// 	printf("%d : %f %f %f \n", i, rays[i].dir, rays[i].dir.x, rays[i].dir.y);
	// printf(">>>%d\n", map[5][5]);
	map[10][1] = 1;
	map[10][2] = 1;
	map[10][3] = 1;
	map[10][4] = 1;
	map[5][6] = 1;
	map[5][8] = 1;
	map[5][10] = 1;
	// i = 400;
	// j = -50;
	// while (++i < 600)
	// {
	// 	map[i][100 + j] = 1;
	// 	j++;
	// }
	window(map, player, rays);
}
