/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:09:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/13 10:03:03 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"


static	void	frame_init(t_arg *arg)
{
	arg->frame->img = mlx_new_image(arg->mlx, X_RES, Y_RES);
	if (!arg->frame->addr)
		exit(EXIT_FAILURE);
	arg->frame->addr = mlx_get_data_addr(arg->frame->img, &arg->frame->bpp,
			&arg->frame->line_len, &arg->frame->endian);
	arg->frame->path = NULL;
}

void	arg_walls_init(t_arg *arg, t_map *map)
{
	arg->no = textures_init(arg, map->no);
	arg->so = textures_init(arg, map->so);
	arg->we = textures_init(arg, map->we);
	arg->ea = textures_init(arg, map->ea);
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
}

static t_arg	*arg_init(t_map *map, t_player player, t_ray *rays)
{
	t_arg		*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		exit(EXIT_FAILURE);
	arg->mlx = mlx_init();
	if (!arg->mlx)
		exit(EXIT_FAILURE);
	arg->mlx_win = mlx_new_window(arg->mlx, X_RES, Y_RES, "raycaster");
	if (!arg->mlx_win)
		exit(EXIT_FAILURE);
	arg->frame = malloc(sizeof(t_img));
	if (!arg->frame)
		exit(EXIT_FAILURE);
	frame_init(arg);
	arg->map = map->map;
	arg->player = player;
	arg->rays = rays;
	arg->horizontal_vector = 0;
	arg->vertical_vector = 0;
	arg->moment_vector = 0;
	arg->ground_color = map->floor_c;
	arg->roof_color = map->ceiling_c;
	arg->s_map = map;
	return (arg);
}

int	next_frame(t_arg *arg)
{
	move(arg, 10, arg->horizontal_vector, arg->vertical_vector);
	turn(arg, PI / 64, arg->moment_vector);
	rays_gen(&(arg->player), arg->rays);
	put_walls(arg, arg->rays);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	return (0);
}

void	window(t_map *map, t_player player, t_ray *rays)
{
	t_arg		*arg;

	arg = arg_init(map, player, rays);
	arg_walls_init(arg, map);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	mlx_hook(arg->mlx_win, 17, 0, ft_exit_success, arg);
	mlx_hook(arg->mlx_win, 2, 1L << 0, pressed, arg);
	mlx_hook(arg->mlx_win, 3, 1L << 1, unpressed, arg);
	mlx_loop_hook(arg->mlx, next_frame, arg);
	mlx_loop(arg->mlx);
}
