/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:28:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/12 18:29:50 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

static t_img	textures_init(t_arg *arg, char *path)
{
	t_img	sprite;

	sprite.path = path;
	sprite.img = mlx_xpm_file_to_image(arg->mlx, sprite.path, &sprite.width,
			&sprite.height);
	if (!sprite.img)
		exit(12);
	sprite.addr = mlx_get_data_addr(sprite.img, &sprite.bpp,
			&sprite.line_len, &sprite.endian);
	if (!sprite.addr)
		exit(12);
	return (sprite);
}

void	arg_walls_init(t_arg *arg)
{
	arg->no = textures_init(arg, "Wall1.xpm");//
	arg->so = textures_init(arg, "Wall2.xpm");//
	arg->we = textures_init(arg, "Wall3.xpm");//
	arg->ea = textures_init(arg, "wall4.xpm");//
}

unsigned int	color_from_texture(t_img *texture, int x, int y)
{
	unsigned int	color;
	t_pixel			wall;

	wall.x = x % (int)DIV;
	wall.y = y;
	color = *(unsigned int *)(texture->addr + (wall.y * texture->line_len
				+ wall.x * (texture->bpp / 8)));
	return (color);
}
