/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:14:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/12 18:18:26 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

void	ray_len(t_point start, t_ray *ray, char **map)
{		
	t_point	ray_pos;

	ray_pos.x = start.x;
	ray_pos.y = start.y;
	while (!in_wall(ray_pos, map))
		ray_pos = goto_next_edge(ray_pos, (ray));
	ray->start = start;
	ray->size = sqrt(pow(ray_pos.x - start.x, 2) + pow(ray_pos.y - start.y, 2));
	ray->end.x = ray_pos.x;
	ray->end.y = ray_pos.y;
}

void	find_perpendicular_len(t_arg *arg, t_ray *ray)
{
	double			beta;

	beta = arg->player.cam.dist
		/ sqrt(pow(arg->player.cam.dir.x - ray->start.x, 2)
			+ pow(arg->player.cam.dir.y - ray->start.y, 2));
	ray->size = ray->size * sin(atan(beta));
}
