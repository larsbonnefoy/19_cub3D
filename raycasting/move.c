/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 20:16:23 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 14:27:00 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static t_point	movement(t_point vect_cam, double speed, int x, int y)
{
	t_point	res;
	double	res_size;

	res.x = 0;
	res.y = 0;
	if (y == -1 || y == 1)
	{
		res.x -= y * vect_cam.x;
		res.y -= y * vect_cam.y;
	}
	if (x == -1 || x == 1)
	{
		res.x -= x * vect_cam.y;
		res.y += x * vect_cam.x;
	}
	res_size = sqrt(pow(res.x, 2) + pow(res.y, 2));
	res.x = res.x / res_size;
	res.y = res.y / res_size;
	res.x *= speed;
	res.y *= speed;
	return (res);
}

void	add_movement(t_arg *arg, t_point move_vector)
{
	t_point	pos;

	pos.x = move_vector.x + arg->player.pos.x;
	pos.y = move_vector.y + arg->player.pos.y;
	if (!in_wall(pos, arg->map))
	{
		arg->player.pos.x += move_vector.x;
		arg->player.cam.dir.x += move_vector.x;
		arg->player.cam.start.x += move_vector.x;
		arg->player.cam.end.x += move_vector.x;
		arg->player.pos.y += move_vector.y;
		arg->player.cam.dir.y += move_vector.y;
		arg->player.cam.start.y += move_vector.y;
		arg->player.cam.end.y += move_vector.y;
	}
}

void	move(t_arg *arg, double speed, int x, int y)
{
	double	cam_dist;
	t_point	move_vector;
	t_point	vect_cam;

	vect_cam.x = (arg->player.cam.dir.x - arg->player.pos.x);
	vect_cam.y = (arg->player.cam.dir.y - arg->player.pos.y);
	cam_dist = sqrt(pow(vect_cam.x, 2) + pow(vect_cam.y, 2));
	vect_cam.x = vect_cam.x / cam_dist;
	vect_cam.y = vect_cam.y / cam_dist;
	move_vector = movement(vect_cam, speed, x, y);
	add_movement(arg, move_vector);
}
