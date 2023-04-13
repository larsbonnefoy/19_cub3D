/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_edge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:11:07 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/11 12:55:25 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

static void	set_face(t_ray *ray, double dist_wall_v, double dist_wall_h)
{
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
}

static t_point	next_edge(t_point wallh, t_point wallv, double dist_wall[2])
{
	t_point	res;

	if (dist_wall[H] <= dist_wall[V])
		res = wallh;
	else
		res = wallv;
	return (res);
}

t_point	goto_next_edge(t_point start, t_ray *ray)
{
	t_point	wallh;
	t_point	wallv;
	double	fct[2];
	double	dist_wall[2];

	fct[SLOPE] = ray->dir.y / ray->dir.x;
	fct[B] = start.y - (fct[SLOPE] * start.x);
	if (ray->dir.x > 0)
		wallv.x = ((((int)start.x / DIV) + 1) * DIV);
	else
		wallv.x = (((((int)start.x) / DIV)) * DIV) - 0.00000000001;
	if (ray->dir.y > 0)
		wallh.y = ((((int)start.y / DIV) + 1) * DIV);
	else
		wallh.y = ((((int)start.y / DIV)) * DIV) - 0.00000000001;
	wallv.y = fct[SLOPE] * wallv.x + fct[B];
	wallh.x = (wallh.y - fct[B]) / fct[SLOPE];
	dist_wall[V] = sqrt(pow(start.x - wallv.x, 2) + pow(start.y - wallv.y, 2));
	dist_wall[H] = sqrt(pow(start.x - wallh.x, 2) + pow(start.y - wallh.y, 2));
	set_face(ray, dist_wall[V], dist_wall[H]);
	return (next_edge(wallh, wallv, dist_wall));
}
