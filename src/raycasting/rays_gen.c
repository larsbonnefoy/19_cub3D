/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:25:41 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/11 14:36:37 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	rays_gen(t_player *player, t_ray rays[X_RES])
{
	t_point	ray_incr;
	int		i;
	t_point	cam_dir;
	double	ray_norm;
	t_point	pos;

	cam_dir.x = player->cam.end.x - player->cam.start.x;
	cam_dir.y = player->cam.end.y - player->cam.start.y;
	cam_dir.x = (cam_dir.x / player->cam.size);
	cam_dir.y = (cam_dir.y / player->cam.size);
	ray_incr.x = fabs(player->cam.end.x - player->cam.start.x) / ((X_RES) - 1);
	ray_incr.y = fabs(player->cam.end.y - player->cam.start.y) / ((X_RES) - 1);
	pos = player->cam.start;
	i = -1;
	while (++i < X_RES)
	{
		pos.x += ((ray_incr.x) * (cam_dir.x));
		pos.y += ((ray_incr.y) * (cam_dir.y));
		rays[i].dir.x = pos.x - player->pos.x;
		rays[i].dir.y = pos.y - player->pos.y;
		rays[i].start = pos;
		ray_norm = sqrt(pow(rays[i].dir.x, 2) + pow(rays[i].dir.y, 2));
		rays[i].dir.x = rays[i].dir.x / ray_norm;
		rays[i].dir.y = rays[i].dir.y / ray_norm;
	}
}
