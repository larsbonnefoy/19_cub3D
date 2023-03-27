/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/27 22:34:17 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	rays_gen(t_player *player, t_ray rays[X_RES])
{
	t_point	ray_incr;
	int		i;
	t_point	cam_dir;
	double	cam_dir_norm;
	double	ray_norm;
	double	y;
	double	x;

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
		ray_norm = sqrtf(powf(rays[i].dir.x, 2) + powf(rays[i].dir.y, 2));
		rays[i].dir.x = rays[i].dir.x /ray_norm;
		rays[i].dir.y = rays[i].dir.y /ray_norm;
	}
}

int	in_wall(t_point pos, int **map)
{
	printf(">>>%d\n", map[(int)pos.y][(int)pos.x]);
	if (map[(int)pos.y][(int)pos.x])
		return (1);
	return (0);
}

static t_point goto_next_edge(t_point pos, t_ray *ray)
{
	t_point	res;
	
	res = pos;
	// while ((int)res.x == (int)pos.x && (int)res.y == (int)pos.y)
	// {
		// printf("test\n");
		res.x += ray->dir.x;
		res.y += ray->dir.y;
	// }
	res.x = res.x;
	res.y = res.y;
	return res;
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
		// printf("# %lf %lf %lf %lf\n", i, ray_pos.x, ray_pos.y, player->pos.x, player->pos.y);
		rays[i].size = sqrt(pow(ray_pos.x - player->pos.x, 2) + pow(ray_pos.y - player->pos.y, 2));
		// printf("size %lf\n", pow(ray_pos.x - player->pos.x, 2) + pow(ray_pos.y - player->pos.y, 2));
	}
}

int	main()
{
	t_ray 		rays[X_RES];
	t_player	player;
	int			i;
	int			j;
	int			val;
	int 		**map;
	
	map = malloc(sizeof(int *) * 11);
	i = -1;
	while(++i < 10)
	{
		map[i] = malloc(sizeof(int) * 11);
		j = -1;
		while (++j < 10);
		{
			val = 0;
			if (i == 0 || j == 0 || i == 9 || j == 9)
				val = 1;
			map[i][j] = val;
			printf("wtf frero %d %d\n", map[i][j], val);
		}
		printf("hmmmmmmm %d %d\n", map[i][j], val);
	}
	printf("1>>>%d\n", map[0][0]);
// 	player.pos.x = 5;
// 	player.pos.y = 5;
// 	player.cam.size = 9;
// 	player.cam.dir.x = 5;
// 	player.cam.dir.y = 4;
// 	player.cam.start.x = 1;
// 	player.cam.start.y = 4;
// 	rays_gen(&player, rays);
// 	i = -1;
// 	// while (++i < X_RES)
// 	// 	printf("%d : %f %f \n", i, rays[i].dir.x, rays[i].dir.y);
// 	rays_len(&player, rays, map);
// 	// while (++i < X_RES)
// 	// 	printf("%d : %f %f %f \n", i, rays[i].dir, rays[i].dir.x, rays[i].dir.y);
// 	// printf(">>>%d\n", map[5][5]);
// 	// window(map, player, rays);
}
