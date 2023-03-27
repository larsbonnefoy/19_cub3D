/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:09:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/27 22:27:26 by hdelmas          ###   ########.fr       */
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

static void	set_pixel_color(t_img *dst, t_pixel pxl, size_t	clr)
{
	char	*pxl_addr;

	pxl_addr = dst->addr + ((pxl.y) * dst->line_len + (pxl.x) * (dst->bpp / 8));
	*(size_t *)pxl_addr = clr;
}

static void	draw_first_frame(t_arg *arg)
{
	t_pixel	pixel;


	while (pixel.y < Y_RES)
	{
		pixel.x= 0;
		while (pixel.x < X_RES)
		{
			set_pixel_color(arg->frame, pixel, 8684676);
			pixel.x+= 1;
		}
		pixel.y+= 1;
	}
}

static t_point draw_ray(t_arg *arg, t_point pos, t_ray *ray)
{
	t_point	res;
	t_pixel	pxl;
	int		i;
	
	res = pos;
	res.x += ray->dir.x;
	res.y += ray->dir.y;
	i = -1;
	pxl.x = res.x;
	pxl.y = res.y;
	while (++i < X_RES)
	{
		pxl.x += ray->dir.x;
		pxl.y += ray->dir.y;
		printf("beep");
		set_pixel_color(arg->frame, pxl, 5083746);
	}
	res.x = res.x;
	res.y = res.y;
	return res;
}

void	put_rays(t_arg *arg, t_ray *rays)
{
	int			i;
	t_point	ray_pos;
	
	i = -1;
	printf("rays\n");
	while (++i < X_RES)
	{
		ray_pos = arg->player.pos;
		printf("hmmmm %f %f %d\n", ray_pos.x, ray_pos.y, in_wall(ray_pos, arg->map));
		while (!in_wall(ray_pos, arg->map))
			ray_pos = draw_ray(arg, ray_pos, &(arg->rays[i]));
	}
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
}

int	key_hook(int keycode, t_arg *arg)
{
	// int		check;
	// char	*steps;

	// check = -1;
	 if (keycode == ESC)
		ft_exit_success(arg);
	if (keycode == W || keycode == UP)
		printf("up\n");
		// check = moveup(arg);
	// if (keycode == S || keycode == DOWN)
	// 	check = movedown(arg);
	// if (keycode == D || keycode == RIGHT)
	// 	check = moveright(arg);
	// if (keycode == A || keycode == LEFT)
	// 	check = moveleft(arg);
	// if (check == -1)
	// 	return (-1);
	put_rays(arg, arg->rays);
	return (0);
}

void	window(int **map, t_player player, t_ray *rays)
{
	t_arg		*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		exit(EXIT_FAILURE);
	arg->mlx = mlx_init();
	if (!arg->mlx)
		exit(EXIT_FAILURE);
	arg->mlx_win = mlx_new_window(arg->mlx, X_RES,
			Y_RES, "raycaster");
	// mlx_loop(arg->mlx);
	if (!arg->mlx_win)
		exit(EXIT_FAILURE);
	arg->frame = malloc(sizeof(t_img));
	if (!arg->frame)
		exit(EXIT_FAILURE);
	arg->map = map;
	printf(">>>%d\n", map[5][5]);
	// arg->player = player;
	// arg->rays = rays;
	// int  i = -1;
	// while (++i < X_RES)
	// 	printf("%d : %f %f %f\n", i, arg->rays[i].dir.x, arg->rays[i].dir.y, arg->rays[i].size);
	// arg->frame->img = mlx_new_image(arg->mlx, X_RES, Y_RES);
	// if (!arg->frame->addr)
	// 	exit(EXIT_FAILURE);
	// arg->frame->addr = mlx_get_data_addr(arg->frame->img, &arg->frame->bpp,
	// 		&arg->frame->line_len, &arg->frame->endian);
	// arg->frame->path = NULL;
	// if (!arg->frame->addr)
	// 	exit(EXIT_FAILURE);
	// draw_first_frame(arg);	
	// mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	// mlx_hook(arg->mlx_win, 17, 0, ft_exit_success, arg);
	// mlx_key_hook(arg->mlx_win, key_hook, arg);
	// mlx_loop(arg->mlx);
}
