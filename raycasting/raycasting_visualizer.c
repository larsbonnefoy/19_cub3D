/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:09:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 00:01:15 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int	ft_exit_success(t_arg *arg)
{
	mlx_destroy_image(arg->mlx, arg->frame->img);
	mlx_destroy_window(arg->mlx, arg->mlx_win);
	exit(EXIT_SUCCESS);
	return (1);
}

static	void	frame_init(t_arg *arg)
{
	arg->frame->img = mlx_new_image(arg->mlx, X_RES, Y_RES);
	if (!arg->frame->addr)
		exit(EXIT_FAILURE);
	arg->frame->addr = mlx_get_data_addr(arg->frame->img, &arg->frame->bpp,
			&arg->frame->line_len, &arg->frame->endian);
	arg->frame->path = NULL;
}

static t_arg	*arg_init(char **map, t_player player, t_ray *rays)
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
	arg->map = map;
	arg->player = player;
	arg->rays = rays;
	arg->horizontal_vector = 0;
	arg->vertical_vector = 0;
	arg->moment_vector = 0;
	arg->ground_color = 0xece75f;
	arg->roof_color = 0x3CB371;
	return (arg);
}

int	next_frame(t_arg *arg)
{
	move(arg, 10, arg->horizontal_vector, arg->vertical_vector);
	turn(arg, PI / 48, arg->moment_vector);
	rays_gen(&(arg->player), arg->rays);
	put_walls(arg, arg->rays);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
}


void	window(char **map, t_player player, t_ray *rays)
{
	t_arg		*arg;

	arg = arg_init(map, player, rays);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	mlx_hook(arg->mlx_win, 17, 0, ft_exit_success, arg);
	mlx_hook(arg->mlx_win, 2, 1L << 0, pressed, arg);
	mlx_hook(arg->mlx_win, 3, 1L << 1, unpressed, arg);
	mlx_loop_hook(arg->mlx, next_frame, arg);
	mlx_loop(arg->mlx);
}
