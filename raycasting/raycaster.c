/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/30 20:33:48 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	rays_gen(t_player *player, t_ray rays[X_RES])
{
	t_point	ray_incr;
	int		i;
	t_point	cam_dir;
	t_point	cam_end;
	double	cam_dir_norm;
	double	ray_norm;
	double	y;
	double	x;

	ray_incr.x = (fabs(player->cam.dir.x - player->cam.start.x) * 2) / (X_RES - 1);
	ray_incr.y = (fabs(player->cam.dir.y - player->cam.start.y) * 2) / (X_RES - 1);
	printf("ray gen >incr %f %f\n", ray_incr.x, ray_incr.y);
	i = -1;
	cam_dir.x = player->cam.dir.x - player->cam.start.x;
	cam_dir.y = player->cam.dir.y - player->cam.start.y;
	cam_dir_norm = sqrtf(pow(cam_dir.x, 2) + pow(cam_dir.y, 2));
	printf("ray  gen :cam %d norm %f\n", i, cam_dir_norm);
	cam_dir.x = cam_dir.x / cam_dir_norm;
	cam_dir.y = cam_dir.y / cam_dir_norm;
	cam_end.x = player->cam.start.x + ((ray_incr.x * X_RES - 1) * (cam_dir.x));
	cam_end.y = player->cam.start.y + ((ray_incr.y * X_RES - 1) * (cam_dir.y));
	printf("ray gen :cam dir %f %f\n", cam_dir.x, cam_dir.y);
	while (++i < X_RES)
	{
		x = (player->cam.start.x) + ((ray_incr.x * i) * (cam_dir.x));
		y = player->cam.start.y + ((ray_incr.y * i) * (cam_dir.y));
		rays[i].dir.x = x - player->pos.x;
		rays[i].dir.y = y - player->pos.y;
		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
		// printf("ray %d norm %f\n", i, ray_norm);
		rays[i].dir.x = rays[i].dir.x / ray_norm;
		rays[i].dir.y = rays[i].dir.y / ray_norm;
		// printf("ray[%d].dir x=%f y=%f\n", i,rays[i].dir.x, rays[i].dir.y);
	}
	// printf("x=%f y=%f\n", x, y);
}

int	in_wall(t_point pos, int **map)
{
	if (!(pos.x < X_RES && pos.x >= 0 && pos.y < Y_RES && pos.y >= 0) || map[(int)pos.y][(int)pos.x])
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
	res.x = res.x;
	res.y = res.y;
	return (res);
}

void	ray_len(t_point start, t_ray *ray, int **map)
{		
		t_point	ray_pos;

		while (!in_wall(ray_pos, map))
			ray_pos = goto_next_edge(ray_pos, (ray));
		ray->start.x = start.x;
		ray->start.y = start.y;
		ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
		ray->end.x = ray_pos.x;
		ray->end.y = ray_pos.y;
		printf("ray len : rayend.x = %f .y = %f\n", ray->end.x, ray->end.y);
}

void	rays_len(t_player *player, t_ray rays[X_RES], int **map)
{
	int	i;
	t_point	ray_pos;

	i = -1;
	while (++i < X_RES)
	{
		ray_pos = player->pos;
		while (!in_wall(ray_pos, map))
			ray_pos = goto_next_edge(ray_pos, &(rays[i]));
		rays[i].size = sqrt(pow(ray_pos.x - player->pos.x, 2) + pow(ray_pos.y - player->pos.y, 2));
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
	
	map = (int **)malloc(sizeof(int *) * 1000);
	i = -1;
	while(++i < 1000)
	{
		sub = (int *)malloc(sizeof(int) * 1000);
		j = -1;
		while (++j < 1000)
		{
			val = 0;
			if (i == 0 || j == 0 || i == 999 || j == 999 /*|| i == 400 || j == 400 || i == 600 || j == 600*/)
				val = 1;
			sub[j] = val;
		}
		map[i] = sub;
	}
	player.pos.x = 500;
	player.pos.y = 500;
	player.cam.size = 100;
	player.cam.dir.x = player.pos.x ;
	player.cam.dir.y = player.pos.y + 100;
	player.cam.start.x = player.cam.dir.x - player.cam.size / 2;
	player.cam.start.y = player.cam.dir.y  ;
	rays_gen(&player, rays);
	i = -1;
	// while (++i < X_RES)
	// 	printf("%d : %f %f \n", i, rays[i].dir.x, rays[i].dir.y);
	// rays_len(&player, rays, map);
	// while (++i < X_RES)
	// 	printf("%d : %f %f %f \n", i, rays[i].dir, rays[i].dir.x, rays[i].dir.y);
	printf(">>>%d\n", map[5][5]);
	// map[240][450] = 1;
	// map[240][449] = 1;
	// map[240][451] = 1;
	// map[230][440] = 1;
	// map[230][441] = 1;
	// map[230][442] = 1;
	// map[230][443] = 1;
	window(map, player, rays);
}
