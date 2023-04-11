/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:57:17 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/11 10:59:11 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static t_img	textures_init(t_arg *arg, char *path)
{
	t_img	sprite;

	sprite.path = path;
	sprite.img = mlx_xpm_file_to_image(arg->mlx, sprite.path, &sprite.width,
			&sprite.height);
	// if (!sprite.img)
	// 	ft_exit_failure(arg);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bpp,
			&sprite.line_len, &sprite.endian);
	// if (!sprite.addr)
	// 	ft_exit_failure(arg);
	return (sprite);
}

void	arg_walls_init(t_arg *arg)
{
	arg->walls.no = textures_init(arg, "wall1.xpm");
	arg->walls.so = textures_init(arg, "wall2.xpm");
	arg->walls.we = textures_init(arg, "wall3.xpm");
	arg->walls.ea = textures_init(arg, "wall4.xpm");
}

static void	set_pixel_color(t_img *dst, t_pixel pxl, size_t	clr)
{
	char	*pxl_addr;

	pxl_addr = dst->addr + ((pxl.y) * dst->line_len + (pxl.x) * (dst->bpp / 8));
	*(size_t *)pxl_addr = clr;
}

static unsigned int	set_color(char face)
{
	unsigned int	color;

	color = 0xff00ff;
	if (face == 'W')
		color = 0x0000ff;
	if (face == 'N')
		color = 0x00ff00;
	if (face == 'S')
		color = 0xff0000;
	if (face == 'E')
		color = 0xff00ff;
	return (color);
}

static void	draw_wall(t_arg *arg, t_ray *ray, t_img *frame, int x)
{
	int				y;
	int				wall_size ;
	t_pixel			pxl;
	unsigned int	color;
	double			beta;

	y = -1;
	// beta = arg->player.cam.dist / sqrt(pow(arg->player.cam.dir.x - ray->start.x, 2) + pow(arg->player.cam.dir.y - ray->start.y, 2));
	// ray->size = ray->size * sin(atan(beta));
	wall_size = (X_RES / ray->size) * (DIV * (arg->player.cam.dist / arg->player.cam.size));
	pxl.x = x;
	while (++y < Y_RES)
	{
		pxl.y = y;
		if (y <= (Y_RES / 2) - wall_size / 2)
			set_pixel_color(frame, pxl, arg->ground_color);
		else if (y >= (Y_RES / 2) + wall_size / 2)
			set_pixel_color(frame, pxl, arg->roof_color);
		else
		{
			color = set_color(ray->face[0]);
			set_pixel_color(frame, pxl, color);
		}
	}
}

void	put_walls(t_arg *arg, t_ray *rays)
{
	int			i;
	t_point		ray_pos;

	i = -1;
	ray_pos = arg->player.pos;
	while (++i < X_RES)
	{
		ray_len(ray_pos, &(rays[i]), arg->map);
		draw_wall(arg, &(rays[i]), arg->frame, i);
	}
}
