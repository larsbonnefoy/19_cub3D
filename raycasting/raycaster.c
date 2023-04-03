/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/03 19:06:25 by hdelmas          ###   ########.fr       */
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
	double	ray_norm;
	double	y;
	double	x;

	cam_dir.x = player->cam.end.x - player->cam.start.x;
	cam_dir.y = player->cam.end.y - player->cam.start.y;
	cam_dir.x = (cam_dir.x / player->cam.size);
	cam_dir.y = (cam_dir.y / player->cam.size);
	ray_incr.x = fabs((player->cam.end.x - player->cam.start.x)) / ((X_RES) - 1);
	ray_incr.y = fabs((player->cam.end.y - player->cam.start.y)) / ((X_RES) - 1);
	i = -1;
	x = player->cam.start.x;
	y = player->cam.start.y;
	while (++i < X_RES)
	{
		x += ((ray_incr.x) * (cam_dir.x));
		y += ((ray_incr.y) * (cam_dir.y));
		rays[i].dir.x = x - player->pos.x;
		rays[i].dir.y = y - player->pos.y;
		rays[i].start.x = x;
		rays[i].start.y = y;
		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
		rays[i].dir.x = rays[i].dir.x / ray_norm;
		rays[i].dir.y = rays[i].dir.y / ray_norm;
	}
}

int	in_wall(t_point pos, char **map)
{
	if (!(pos.x < X_RES && pos.x >= 0 && pos.y < Y_RES && pos.y >= 0) || map[(int)pos.y / 64][(int)pos.x / 64] == '1')
		return (1);
	return (0);
}

static char	*set_face(t_point pos, t_point last_pos, t_point dir)
{
	t_point	sq_tl;
	t_point	sq_br;
	double	c;
	t_point	entry;
	t_point	exit;

	if (dir.x == 0)
	{
		if (last_pos.y < pos.y)
			return ("N");
		else
			return ("S");
	}
	if (dir.y == 0)
	{
		if (last_pos.x < pos.x)
			return ("W");
		else
			return ("E");
	}
	sq_tl.x = (int) pos.x; 
	sq_tl.y = (int) pos.y;
	sq_br.x = sq_tl.x + 64; 
	sq_br.y = sq_tl.y + 64;
	c = -dir.x * last_pos.x - dir.y * last_pos.y;
	//ABCD a square
	//try AD
	entry.x = sq_tl.x;
	entry.y = (1 / dir.x) * (dir.y * entry.x + c);
	if (entry.y <= sq_br.y && entry.y >= sq_tl.y && entry.x <= pos.x && entry.x >= last_pos.x)
		return ("W");
	//try BC
	entry.x = sq_br.x;
	entry.y = (1 / dir.x) * (dir.y * entry.x + c);
	if (entry.y <= sq_br.y && entry.y >= sq_tl.y && entry.x >= pos.x && entry.x <= last_pos.x)
		return ("E");
	entry.y = sq_tl.y;
	entry.x = (1 / dir.y) * (dir.x * entry.y - c);
	if (entry.x <= sq_br.x && entry.x >= sq_tl.x && entry.y >= pos.y && entry.y <= last_pos.y)
		return ("N");
	entry.y = sq_br.y;
	entry.x = (1 / dir.y) * (dir.x * entry.y - c);
	if (entry.x <= sq_br.x && entry.x >= sq_tl.x && entry.y >= pos.y && entry.y <= last_pos.y)
		return ("S");
	return (NULL);          
}

static t_point	goto_next_edge(t_point pos, t_ray *ray)
{
	t_point	res;

	res = pos;
	// while ((int)res.x == (int)pos.x && (int)res.y == (int)pos.y)
	// {
		res.x += ray->dir.x;
		res.y += ray->dir.y;
	// }
	// res.x = (int)res.x;
	// res.y = (int)res.y;
	return (res);
}

void	ray_len(t_point start, t_ray *ray, char **map)
{		
		t_point	ray_pos;

		ray_pos = start;
		while (!in_wall(ray_pos, map))
			ray_pos = goto_next_edge(ray_pos, (ray));
		
		ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
		ray->end.x = ray_pos.x;
		ray->end.y = ray_pos.y;
		// printf("ray len :raydir =  %f %f raystart = %f %f rayend.x = %f .y = %f\n", ray->dir.x, ray->dir.y, ray->start.x, ray->start.y, ray_pos.x, ray_pos.y);
}

void	rays_len(t_player *player, t_ray rays[X_RES], char **map)
{
	int	i;
	t_point	ray_pos;

	i = -1;
	while (++i < X_RES)
	{

		ray_len(rays[i].start, &(rays[i]), map);
	}
}

int	main()
{
	t_ray 		rays[X_RES];
	t_player	player;
	int			i;
	int			j;
	int			val;
	char 		*sub;
	char 		**map;
	
	map = (char **)malloc(sizeof(char *) * Y_RES / 64);
	i = -1;
	while(++i < Y_RES / 64)
	{
		sub = (char *)malloc(sizeof(char) * ((X_RES / 64) + 1));
		sub[(X_RES / 64)] = '\0';
		j = -1;
		while (++j < X_RES / 64)
		{
			val = '0';
			if (i == 0 || j == 0 || i == (Y_RES / 64) - 1|| j == (X_RES / 64) - 1 /*|| i == 400 || j == 400 || i == 600 || j == 600*/)
				val = '1';
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
	player.cam.dist = sqrt(pow(player.cam.dir.x - player.pos.x, 2) + pow(player.cam.dir.y - player.pos.y, 2));
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
	map[10][1] = '1';
	map[10][2] = '1';
	map[10][3] = '1';
	map[10][4] = '1';
	map[5][6] = '1';
	map[5][8] = '1';
	map[5][10] = '1';
	// i = 400;
	// j = -50;
	// while (++i < 600)
	// {
	// 	map[i][100 + j] = 1;
	// 	j++;
	// }
	window(map, player, rays);
}
