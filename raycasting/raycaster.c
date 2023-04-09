/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/09 18:07:26 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static char	*set_face(t_point pos, t_point last_pos, t_point dir)
{
	t_point	sq_tl;
	t_point	sq_br;
	double	c;
	t_point	entry;
	t_point	exit;

	// printf("face : dir = %f %f\n", dir);
	if ( dir.x == 0)
	{
		if (last_pos.y < pos.y)
			return ("N");
		else
			return ("S");
	}
	if ( dir.y == 0)
	{
		if (last_pos.x < pos.x)
			return ("W");
		else
			return ("E");
	}
	sq_tl.x = pos.x; 
	sq_tl.y = pos.y;
	sq_br.x = sq_tl.x + DIV; 
	sq_br.y = sq_tl.y + DIV;
	c = -dir.x * last_pos.x - dir.y * last_pos.y;
	//ABCD a square
	//try AD
	// printf("face : pos = %f %f, last_pos = %f %f\n", pos, last_pos);
	// printf("face : sq_tl = %f %f, sq_br = %f %f\n", sq_tl, sq_br);
	entry.x = sq_tl.x;
	entry.y = (1 / dir.x) * (dir.y * entry.x + c);
	if (entry.y <= sq_br.y && entry.y >= sq_tl.y && entry.x <= pos.x && entry.x >= last_pos.x)
		return ("W");
	entry.x = sq_br.x;
	entry.y = (1 / dir.x) * (dir.y * entry.x + c);
	if (entry.y <= sq_br.y && entry.y >= sq_tl.y && entry.x >= pos.x && entry.x <= last_pos.x)
		return ("E");
	entry.y = sq_tl.y;
	entry.x = (1 / dir.y) * (dir.x * entry.y - c);
	if (entry.x <= sq_br.x && entry.x >= sq_tl.x && entry.y <= pos.y && entry.y >= last_pos.y)
		return ("N");
	entry.y = sq_br.y;
	entry.x = (1 / dir.y) * (dir.x * entry.y - c);
	if (entry.x <= sq_br.x && entry.x >= sq_tl.x && entry.y >= pos.y && entry.y <= last_pos.y)
		return ("S");
	// printf("face : entry = %f %f\n", entry.x, entry.y);
	return ("");          
}

// void	rays_gen(t_player *player, t_ray rays[X_RES])
// {
// 	t_point	ray_incr;
// 	int		i;
// 	t_point	cam_dir;
// 	t_point	cam_end;
// 	t_point	cam_start;
// 	double	ray_norm;
// 	double	y;
// 	double	x;
// 	t_point start;
// 	t_point end;

// 	i = -1;
// 	while (++i < X_RES)
// 	{
// 		x = 2 * (double)i / ((double)(X_RES) - 1) - 1;//x pos line on screen == x pos on the cam line in the cam line space
// 		rays[i].dir.x = (player->cam.dir.x + player->cam.line.x * x) ;
// 		rays[i].dir.y = (player->cam.dir.y + player->cam.line.y * x) ;
// 		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
// 		rays[i].dir.x = rays[i].dir.x / ray_norm;
// 		rays[i].dir.y = rays[i].dir.y / ray_norm;
// 		// printf("gen %f %f\n", rays[i].dir.x, rays[i].dir.y);
// 	}
// }
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
	if (!(pos.x < X_RES && pos.x >= 0 && pos.y < Y_RES && pos.y >= 0) || map[(int)pos.y / DIV][(int)pos.x / DIV] == '1')
		return (1);
	return (0);
}

t_point	goto_next_edge(t_point start, t_ray *ray)
{
	t_point	res;
	t_point	wall_h;
	double dist_wall_h;
	t_point	wall_v;
	double dist_wall_v;
	double	slope;
	double	b;
	
	slope = ray->dir.y / ray->dir.x;
	b = start.y - (slope * start.x);
	if (ray->dir.x > 0)
		wall_v.x = ((((int)start.x / DIV) + 1) * DIV);
	else
		wall_v.x = (((((int)start.x) / DIV)) * DIV) - 1;
	if (ray->dir.y > 0)
		wall_h.y = ((((int)start.y / DIV) + 1) * DIV);
	else
		wall_h.y = ((((int)start.y / DIV)) * DIV) - 1;
	wall_v.y = slope * wall_v.x + b;
	wall_h.x = (wall_h.y - b) / slope;

	dist_wall_v = sqrt(pow(start.x - wall_v.x, 2) + pow(start.y - wall_v.y, 2));
	dist_wall_h = sqrt(pow(start.x - wall_h.x, 2) + pow(start.y - wall_h.y, 2));
	if (dist_wall_h < dist_wall_v)
		res = wall_h;
	else
		res = wall_v;
	if (dist_wall_h < dist_wall_v)
	{
		if (ray->dir.y <= 0)
			ray->face = "S";
		else
			ray->face = "N";
	}
	else
	{
		if (ray->dir.x >= 0)
			ray->face = "W";
		else
			ray->face = "E";
	}
	return (res);
}

void	ray_len(t_point start, t_ray *ray, char **map)
{		
		t_point	ray_pos;
		t_point	last_pos;
		double	dist_wall_x;
		double	dist_wall_y;

		ray_pos.x = start.x;
		ray_pos.y = start.y;
		while (!in_wall(ray_pos, map))
		{
			last_pos = ray_pos;
			ray_pos = goto_next_edge(ray_pos, (ray));

		}
		ray->start = start;
		ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
		ray->end.x = ray_pos.x;
		ray->end.y = ray_pos.y;
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
	
	map = (char **)malloc(sizeof(char *) * Y_RES / DIV);
	i = -1;
	while(++i < Y_RES / DIV)
	{
		sub = (char *)malloc(sizeof(char) * ((X_RES / DIV) + 1));
		sub[(X_RES / DIV)] = '\0';
		j = -1;
		while (++j < X_RES / DIV)
		{
			val = '0';
			if (i == 0 || j == 0 || i == (Y_RES / DIV) - 1|| j == (X_RES / DIV) - 1 /*|| i == 400 || j == 400 || i == 600 || j == 600*/)
				val = '1';
			sub[j] = val;
		}
		map[i] = sub;
	}
	player.pos.x = X_RES / 2 ;
	player.pos.y = Y_RES / 2;
	player.cam.size = 5;
	player.cam.pos.x = player.pos.x;
	player.cam.pos.y = player.pos.y - 10;
	player.cam.line.x = 0.6;
	player.cam.line.y = 0;
	player.cam.dir.x = player.pos.x ;
	player.cam.dir.y = player.pos.y - 10;
	player.cam.start.x = player.cam.dir.x - player.cam.size / 2;
	player.cam.start.y = player.cam.dir.y;
	player.cam.end.x = player.cam.dir.x + player.cam.size / 2;
	player.cam.end.y = player.cam.dir.y;
	player.cam.dist = sqrt(pow(player.cam.dir.x - player.pos.x, 2) + pow(player.cam.dir.y - player.pos.y, 2));
	printf("cam end y %f\n", player.cam.end.y);
	// rays_gen(&player, rays);
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
