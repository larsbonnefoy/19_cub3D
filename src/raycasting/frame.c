/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:57:17 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/12 18:29:20 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static void	set_pixel_color(t_img *dst, t_pixel pxl, size_t	clr)
{
	char	*pxl_addr;

	pxl_addr = dst->addr + ((pxl.y) * dst->line_len + (pxl.x) * (dst->bpp / 8));
	*(size_t *)pxl_addr = clr;
}

static unsigned int	set_color(t_arg *arg, t_ray *ray, char face, int y)
{
	unsigned int	color;

	color = 0xff00ff;
	if (face == 'W')
		color = color_from_texture(&arg->we, ray->end.y, y);
	if (face == 'N')
		color = color_from_texture(&arg->no, ray->end.x, y);
	if (face == 'S')
		color = color_from_texture(&arg->so, ray->end.x, y);
	if (face == 'E')
		color = color_from_texture(&arg->ea, ray->end.y, y);
	return (color);
}

static void	set_wall_textures(t_arg *arg, t_ray *ray,
	t_pixel pxl, t_point *j_incr)
{
	unsigned int	color;

	color = set_color(arg, ray, ray->face[0], (int)j_incr->x);
	set_pixel_color(arg->frame, pxl, color);
	j_incr->x = (j_incr->x + j_incr->y);
}

static void	draw_wall(t_arg *arg, t_ray *ray, t_img *frame, int x)
{
	int				y;
	t_point			j_incr;
	double			wall_size ;
	t_pixel			pxl;

	y = -1;
	j_incr.x = 0;
	find_perpendicular_len(arg, ray);
	wall_size = (X_RES / ray->size)
		* (DIV * (arg->player.cam.dist / arg->player.cam.size));
	j_incr.y = DIV / wall_size;
	if (wall_size > Y_RES)
		j_incr.x = (((wall_size - Y_RES) / 2) / wall_size) * DIV;
	pxl.x = x;
	while (++y < Y_RES)
	{
		pxl.y = y;
		if (y < (Y_RES / 2) - (int)(wall_size / 2))
			set_pixel_color(frame, pxl, arg->ground_color);
		else if (y > (Y_RES / 2) + (int)(wall_size / 2))
			set_pixel_color(frame, pxl, arg->roof_color);
		else
			set_wall_textures(arg, ray, pxl, &j_incr);
	}
}

void	put_walls(t_arg *arg, t_ray *rays)
{
	int			i;
	t_point		ray_pos;

	i = -1;
	while (++i < X_RES)
	{
		ray_pos = rays[i].start;
		ray_len(ray_pos, &(rays[i]), arg->map);
		draw_wall(arg, &(rays[i]), arg->frame, i);
	}
}
