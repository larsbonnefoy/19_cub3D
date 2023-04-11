/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:14:56 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/11 14:36:02 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_player(t_player *player)
{
	player->pos.x = X_RES / 2 ;
	player->pos.y = Y_RES / 2;
	set_dir(player, 'N');
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
