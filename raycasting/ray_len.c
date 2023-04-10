/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:14:08 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 14:26:39 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	ray_len(t_point start, t_ray *ray, char **map)
{		
	t_point	ray_pos;
	t_point	last_pos;

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
