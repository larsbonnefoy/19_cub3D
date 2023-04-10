/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 17:20:45 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_player(t_player *player)
{
	player->pos.x = X_RES / 2 ;
	player->pos.y = Y_RES / 2;
	player->cam.size = 10;
	player->cam.pos.x = player->pos.x;
	player->cam.pos.y = player->pos.y + 10;
	// player->cam.line.x = 0.6;
	// player->cam.line.y = 0;
	player->cam.dir.x = player->pos.x ;
	player->cam.dir.y = player->pos.y + 10;
	player->cam.start.x = player->cam.dir.x + player->cam.size / 2;
	player->cam.start.y = player->cam.dir.y;
	player->cam.end.x = player->cam.dir.x - player->cam.size / 2;
	player->cam.end.y = player->cam.dir.y;
	player->cam.dist = sqrt(pow(player->cam.dir.x - player->pos.x, 2) + pow(player->cam.dir.y - player->pos.y, 2));
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
	
	map = (char **)malloc(sizeof(char *) * (X_RES + 1500) / DIV);
	i = -1;
	while(++i < (X_RES + 1500) / DIV)
	{
		sub = (char *)malloc(sizeof(char) * (((X_RES + 1500) / DIV) + 1));
		sub[((X_RES + 1500) / DIV)] = '\0';
		j = -1;
		while (++j < (X_RES + 1500) / DIV)
		{
			val = '0';
			if (i == 0 || j == 0 || i == ((X_RES + 1500) / DIV) - 1|| j == ((X_RES + 1500) / DIV) - 1 /*|| i == 400 || j == 400 || i == 600 || j == 600*/)
				val = '1';
			sub[j] = val;
		}
		map[i] = sub;
	}
	init_player(&player);
	printf("%d\n", (X_RES + 1500) / DIV);

	map[10][1] = '1';
	map[10][2] = '1';
	map[10][3] = '1';
	map[10][4] = '1';
	map[5][6] = '1';
	map[5][8] = '1';
	map[5][10] = '1';
	window(map, player, rays);
}
