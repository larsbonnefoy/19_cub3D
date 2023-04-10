/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:27:00 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/09 22:42:52 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"


static t_point	rotate_point(t_point point, t_point center,
	double ccos, double csin)
{
	t_point	rel_prev;
	t_point	rel;
	t_point	res;

	rel_prev.x = point.x - center.x;
	rel_prev.y = point.y - center.y;
	rel.x = rel_prev.x * ccos + rel_prev.y * csin;
	rel.y = -rel_prev.x * csin + rel_prev.y * ccos;
	res.x = rel.x + center.x;
	res.y = rel.y + center.y;
	return (res);
}

void	turn(t_arg *arg, double rad, int moment)
{
	double	csin;
	double	ccos;

	csin = sin(moment * rad);
	ccos = cos(moment * rad);
	arg->player.cam.dir = rotate_point(arg->player.cam.dir,
			arg->player.pos, ccos, csin);
	arg->player.cam.start = rotate_point(arg->player.cam.start,
			arg->player.pos, ccos, csin);
	arg->player.cam.end = rotate_point(arg->player.cam.end,
			arg->player.pos, ccos, csin);
}
