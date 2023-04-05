/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/05 18:33:36 by hdelmas          ###   ########.fr       */
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

// 	cam_dir.x = player->cam.end.x - player->cam.start.x;
// 	cam_dir.y = player->cam.end.y - player->cam.start.y;
// 	cam_dir.x = fabs(cam_dir.x / player->cam.size);
// 	cam_dir.y = fabs(cam_dir.y / player->cam.size);
// 	ray_incr.x = fabs((player->cam.end.x - player->cam.start.x)) / ((X_RES) - 1);
// 	ray_incr.y = fabs((player->cam.end.y - player->cam.start.y)) / ((X_RES) - 1);
// 	i = -1;
// 	// if 
	
// 	start = player->cam.start;
// 	end = player->cam.end;
// 	player->cam.start = start;
// 	player->cam.end = end;
// 	while (++i < X_RES)
// 	{
// 		start.x += ((ray_incr.x) * (cam_dir.x));
// 		start.y += ((ray_incr.y) * (cam_dir.y));
// 		rays[i].dir.x = start.x - player->pos.x;
// 		rays[i].dir.y = start.y - player->pos.y;
// 		rays[i].start.x = start.x;
// 		rays[i].start.y = start.y;
// 		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
// 		rays[i].dir.x = rays[i].dir.x / ray_norm;
// 		rays[i].dir.y = rays[i].dir.y / ray_norm;
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
	t_point start;
	t_point end;

	i = -1;
	while (++i < X_RES)
	{
		x = 2 * (double)i / ((double)(X_RES) - 1) - 1;//x pos line on screen == x pos on the cam line in the cam line space
		rays[i].dir.x = (player->cam.dir.x + player->cam.line.x * x) ;
		rays[i].dir.y = (player->cam.dir.y + player->cam.line.y * x) ;
		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
		rays[i].dir.x = rays[i].dir.x / ray_norm;
		rays[i].dir.y = rays[i].dir.y / ray_norm;
		// printf("gen %f %f\n", rays[i].dir.x, rays[i].dir.y);
	}
}
int	in_wall(t_point pos, char **map)
{
	if (!(pos.x < X_RES && pos.x >= 0 && pos.y < Y_RES && pos.y >= 0) || map[(int)pos.y / DIV][(int)pos.x / DIV] == '1')
		return (1);
	return (0);
}


// static t_point	goto_next_edge(t_point pos, t_ray *ray)
// {//DDA algorithm
// 	t_point	res;

// 	res = pos;
// 	// while ((int)res.x == (int)pos.x && (int)res.y == (int)pos.y)
// 	// {
// 		res.x += ray->dir.x;
// 		res.y += ray->dir.y;
// 	// }
// 	// res.x = (int)res.x;
// 	// res.y = (int)res.y;
// 	return (res);
// }
t_point	goto_next_edge(t_point start, t_ray *ray)
{//DDA algorithm
	t_point	res;
	t_point	incr;
	t_point	dist_wall;
	t_point	check;
	double	max_incr;
	double	slope;
	double	b;
	
	// printf("fml\n");
	incr = ray->dir;
	// slope = incr.y / incr.x;
	// b = start.y - slope * start.x;
	check.x = 0;
	check.y = 0;
	max_incr = fmax(fabs(incr.x), fabs(incr.y));
	if (incr.x > 0)
		dist_wall.x = fabs(ceil(start.x) - start.x);
	else
		dist_wall.x = fabs((floor(start.x) - (start.x)));
	if (incr.y > 0)
		dist_wall.y = fabs(ceil(start.y) - start.y);
	else
		dist_wall.y = fabs((floor(start.y) - (start.y)));
	// if (dist_wall.x == 0)
	// 	dist_wall.x = 1;
	// if (dist_wall.y == 0)
	// 	dist_wall.y = 1;
	incr.x /= max_incr; 
	incr.y /= max_incr; 
	res.x = ((start.x) + incr.x);
	res.y = ((start.y) + incr.y);
	if (ray->dir.y <= 0  && fabs(start.y - res.y) >= dist_wall.y)
		check.y = -1;
	if (ray->dir.y > 0 && fabs(start.y - res.y) >= dist_wall.y)
		check.y = 1;
	if (ray->dir.x > 0 && fabs(start.x - res.x) >= dist_wall.x)
		check.x = 1;
	if (ray->dir.x <= 0 && fabs(start.x - res.x) >= dist_wall.x)
		check.x = -1;
	// printf(">> %f %f\n", check.x, check.y);
	if (fabs(check.x) == 1 && fabs(check.y) == 1)
	{
		if (fabs(dist_wall.y) > fabs(dist_wall.x))
			check.x = 0;
		else
			check.y = 0;
	}
	if (check.y == -1)
		ray->face = "S";
	if (check.y == 1)
		ray->face = "N";
	if (check.x == 1)
		ray->face = "W";
	if (check.x == -1)
		ray->face = "E";
	return (res);
}
// void	ray_len(t_point start, t_ray *ray, char **map)
// {		
// 		t_point	ray_pos;
// 		t_point	last_pos;

// 		ray_pos = start;
// 		while (!in_wall(ray_pos, map))
// 		{
// 			last_pos = ray_pos;
// 			ray_pos = goto_next_edge(ray_pos, (ray));
// 		}
// 		ray->start = start;
// 		ray->face = set_face(ray_pos, last_pos, ray->dir);
// 		ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
// 		ray->end.x = ray_pos.x;
// 		ray->end.y = ray_pos.y;
// 		// printf("ray len :raydir =  %f %f raystart = %f %f rayend.x = %f .y = %f\n", ray->dir.x, ray->dir.y, ray->start.x, ray->start.y, ray_pos.x, ray_pos.y);
// }

void	ray_len(t_point start, t_ray *ray, char **map)
{		
		t_point	ray_pos;
		t_point	last_pos;
		double	dist_wall_x;
		double	dist_wall_y;

		ray_pos.x = round(start.x);
		ray_pos.y = round(start.y);
		while (!in_wall(ray_pos, map))
		{
			last_pos = ray_pos;
			// printf(">%f %f\n", ray_pos.x, ray_pos.y);
			ray_pos = goto_next_edge(ray_pos, (ray));
			// printf(">>%f %f\n", ray_pos.x, ray_pos.y);
		}
		ray->start = start;
		// ray->face = set_face(ray_pos, last_pos, ray->dir);
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
	player.cam.size = 10;
	player.cam.dir.x = 0;
	player.cam.dir.y = -1;
	player.cam.line.x = 0.5;
	player.cam.line.y = 0;
	// player.cam.start.x = player.cam.dir.x;
	// player.cam.start.y = player.cam.dir.y - player.cam.size / 2;
	// player.cam.end.x = player.cam.dir.x ;
	// player.cam.end.y = player.cam.dir.y + player.cam.size / 2;
	// player.cam.dist = sqrt(pow(player.cam.dir.x - player.pos.x, 2) + pow(player.cam.dir.y - player.pos.y, 2));
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
