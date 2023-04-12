/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dir.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:44:27 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/12 18:08:20 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static void	north(t_player *player)
{
		player->cam.dir.x = player->pos.x ;
		player->cam.dir.y = player->pos.y - 1;
		player->cam.start.x = player->cam.dir.x - player->cam.size / 2;
		player->cam.start.y = player->cam.dir.y;
		player->cam.end.x = player->cam.dir.x + player->cam.size / 2;
		player->cam.end.y = player->cam.dir.y;
}

static void	south(t_player *player)
{
	player->cam.dir.x = player->pos.x ;
	player->cam.dir.y = player->pos.y + 1;
	player->cam.start.x = player->cam.dir.x + player->cam.size / 2;
	player->cam.start.y = player->cam.dir.y;
	player->cam.end.x = player->cam.dir.x - player->cam.size / 2;
	player->cam.end.y = player->cam.dir.y;
}

static void	east(t_player *player)
{
	player->cam.dir.x = player->pos.x + 1;
	player->cam.dir.y = player->pos.y;
	player->cam.start.x = player->cam.dir.x;
	player->cam.start.y = player->cam.dir.y - player->cam.size / 2;
	player->cam.end.x = player->cam.dir.x;
	player->cam.end.y = player->cam.dir.y + player->cam.size / 2;
}

static void	west(t_player *player)
{
	player->cam.dir.x = player->pos.x - 1;
	player->cam.dir.y = player->pos.y;
	player->cam.start.x = player->cam.dir.x;
	player->cam.start.y = player->cam.dir.y + player->cam.size / 2;
	player->cam.end.x = player->cam.dir.x;
	player->cam.end.y = player->cam.dir.y - player->cam.size / 2;
}

void	set_dir(t_player *player, char dir)
{
	player->cam.size = 1;
	if (dir == 'S')
	{
		south(player);
	}
	else if (dir == 'N')
	{
		north(player);
	}
	if (dir == 'E')
	{
		east(player);
	}
	else if (dir == 'W')
	{
		west(player);
	}
	player->cam.dist = sqrt(pow(player->cam.dir.x - player->pos.x, 2)
			+ pow(player->cam.dir.y - player->pos.y, 2));
}
