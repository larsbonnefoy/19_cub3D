/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 11:51:52 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "raycaster.h"
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
			if (i == 0 || j == 0 || i == (Y_RES / DIV) - 1|| j == (X_RES / DIV) - 1 )//|| i == 400 || j == 400 || i == 600 || j == 600)
				val = '1';
			sub[j] = val;
		}
		map[i] = sub;
	}
	player.pos.x = X_RES / 2 ;
	player.pos.y = Y_RES / 2;
	player.cam.size = 10;
	player.cam.pos.x = player.pos.x;
	player.cam.pos.y = player.pos.y - 10;
	// player.cam.line.x = 0.6;
	// player.cam.line.y = 0;
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
*/
