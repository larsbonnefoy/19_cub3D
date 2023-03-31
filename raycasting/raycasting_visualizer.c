/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:09:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/03/31 22:37:52 by hdelmas          ###   ########.fr       */
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

	// printf("->%d %d\n", pxl.x, pxl.y);
	pxl_addr = dst->addr + ((pxl.y) * dst->line_len + (pxl.x) * (dst->bpp / 8));
	*(size_t *)pxl_addr = clr;
}

static void	draw_first_frame(t_arg *arg)
{
	t_pixel	pixel;

	pixel.y = 0;
	while (pixel.y < Y_RES)
	{
		pixel.x = 0;
		while (pixel.x < X_RES)
		{
			set_pixel_color(arg->frame, pixel, 0x3CB371);
			pixel.x+= 1;
		}
		pixel.y+= 1;
	}
}

static t_point draw_ray(t_arg *arg, t_point pos, int i)
{
	t_point	res;
	t_pixel	pxl;

	res = pos;
	res.x += arg->rays[i].dir.x;
	res.y += arg->rays[i].dir.y;
	pxl.x = res.x;
	pxl.y = res.y;
	// printf("%d :  %f %f %d %d %f %f\n", i, arg->rays[i].dir.x, arg->rays[i].dir.y, pxl.x, pxl.y, res.x, res.y);
	set_pixel_color(arg->frame, pxl, 0xece75f);
	return (res);
}

static void	draw_line(t_ray *line, t_img *frame)
{
	t_point	vect_dir;
	t_point	pixel;
	t_pixel	pxl;
	double vect_dir_norm;
	double	slope;

	vect_dir.x = line->dir.x;
	vect_dir.y = line->dir.y;
	vect_dir_norm = line->size - 1;
	pixel.x = line->start.x;
	pixel.y = line->start.y;
	while (vect_dir_norm >= 0)
	{
		pxl.x = pixel.x;
		pxl.y = pixel.y;
		set_pixel_color(frame, pxl, 0x0);
		pixel.x += vect_dir.x;
			pixel.y += (vect_dir.y);
		--vect_dir_norm;
	}
}
static void	draw_line(t_ray *ray, t_img *frame)
{
	
}

void	put_rays(t_arg *arg, t_ray *rays)
{
	int			i;
	int			j;
	t_point	ray_pos;
	
	i = -1;
	while (++i < X_RES)
	{
		ray_pos = arg->player.pos;
		// printf("hmmmm %f %f %d\n", ray_pos.x, ray_pos.y, in_wall(ray_pos, arg->map));
		// j = 0;
		// while (!in_wall(ray_pos, arg->map))
		// {
		// 	j++;
		// 	ray_pos = draw_ray(arg, ray_pos, i);
		// }
		// printf("hello %d %d\n", i, j);
		ray_len(ray_pos, &(rays[i]), arg->map);
		// printf("put ray %d initial pos > %f %f %f %f dir = %f %f end pos %f %f \n", i, ray_pos.x, ray_pos.y, rays[i].start.x, rays[i].start.y, rays[i].dir.x, rays[i].dir.y, rays[i].end.x, rays[i].end.y);
		draw_line(&(rays[i]), arg->frame);
		// // printf("ray %d end pos > %f %f\n", i, ray_pos.x, ray_pos.y);
	}
}

void	turn(t_arg *arg, double rad)
{
	t_point	rel_cam_prev;
	t_point	rel_start_prev;
	t_point	rel_end_prev;
	t_point	rel_cam;
	t_point	rel_start;
	t_point	rel_end;
	double	csin;
	double	ccos;
	double	start_sin;
	double	start_cos;
	double	end_sin;
	double	end_cos;

	csin = sin(rad);
	ccos = cos(rad);
	// arg->player.cam.theta += rad;
	rel_cam_prev.x = arg->player.cam.dir.x - arg->player.pos.x;
	rel_cam_prev.y = arg->player.cam.dir.y - arg->player.pos.y;
	rel_start_prev.x = arg->player.cam.start.x - arg->player.pos.x;
	rel_start_prev.y = arg->player.cam.start.y - arg->player.pos.y;
	rel_end_prev.x = arg->player.cam.end.x - arg->player.pos.x;
	rel_end_prev.y = arg->player.cam.end.y - arg->player.pos.y;
	// printf("prev cam dir %f %f\n", arg->player.cam.dir.x, arg->player.cam.dir.y);
	// printf("prev rel cam dir %f %f | %f %f\n", rel_cam_prev.x, rel_cam_prev.y, ccos, csin);
	// printf("prev start dir %f %f\n", arg->player.cam.start.x, arg->player.cam.start.y);
	// printf("prev rel start dir %f %f \n", rel_start.x, rel_start.y);
	rel_cam.x = rel_cam_prev.x * ccos + rel_cam_prev.y * csin; 
	rel_cam.y = -rel_cam_prev.x * csin + rel_cam_prev.y * ccos;
	rel_start.x = rel_start_prev.x * ccos + rel_start_prev.y * csin;
	rel_start.y = -rel_start_prev.x * csin + rel_start_prev.y * ccos;
	rel_end.x = rel_end_prev.x * ccos + rel_end_prev.y * csin;
	rel_end.y = -rel_end_prev.x * csin + rel_end_prev.y * ccos;
	arg->player.cam.dir.x = rel_cam.x + arg->player.pos.x;
	arg->player.cam.dir.y = rel_cam.y + arg->player.pos.y;
	arg->player.cam.start.x = rel_start.x + arg->player.pos.x;
	arg->player.cam.start.y = rel_start.y + arg->player.pos.y;
	arg->player.cam.end.x = rel_end.x + arg->player.pos.x;
	arg->player.cam.end.y = rel_end.y + arg->player.pos.y;
	// printf("cam dir %f %f\n", arg->player.cam.dir.x, arg->player.cam.dir.y);
	// printf("rel cam dir %f %f\n", rel_cam.x, rel_cam.y);
	// printf(" start dir %f %f\n", arg->player.cam.start.x, arg->player.cam.start.y);
	// printf(" rel start dir %f %f \n", rel_start.x, rel_start.y);
}
void	move(t_arg *arg, double x, double y)
{
	arg->player.pos.x += x;
	arg->player.pos.y += y;
	arg->player.cam.dir.x += x;
	arg->player.cam.dir.y += y;
	arg->player.cam.start.x += x;
	arg->player.cam.start.y += y;
	arg->player.cam.end.x += x;
	arg->player.cam.end.y += y;
}

int	key_hook(int keycode, t_arg *arg)
{
	// int		check;
	// char	*steps;

	// check = -1;
	printf("%d\n", keycode);
	 if (keycode == ESC)
		ft_exit_success(arg);
	if (keycode == W || keycode == UP)
		move(arg, 0, -10);
	if (keycode == S || keycode == DOWN)
		move(arg, 0, 10);
	if (keycode == D)
		move(arg, 10, 0);
	if (keycode == A)
		move(arg, -10, 0);
	if (keycode == RIGHT)
		turn(arg, -PI / 24);
	if (keycode == LEFT)
		turn(arg, PI / 24);
	// if (check == -1)
	// 	return (-1);
	printf(">>> HOOK cam dir %f %f cam start %f %f cam end %f %f\n", arg->player.cam.dir.x, arg->player.cam.dir.y, arg->player.cam.start.x, arg->player.cam.start.y, arg->player.cam.end.x, arg->player.cam.end.y);
	draw_first_frame(arg);
	rays_gen(&(arg->player), arg->rays);
	// draw_first_frame(arg);
	// t_point	oi;
	// oi.x = 55;
	// oi.y = 955;
	// draw_line(arg->player.pos, oi, arg->frame);
	printf("oi\n");
	put_rays(arg, arg->rays);
	printf("oi1\n");
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);

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
	arg->mlx_win = mlx_new_window(arg->mlx, X_RES, Y_RES, "raycaster");
	if (!arg->mlx_win)
		exit(EXIT_FAILURE);
	arg->frame = malloc(sizeof(t_img));
	if (!arg->frame)
		exit(EXIT_FAILURE);
	arg->map = map;
	arg->player = player;
	arg->rays = rays;
	printf(">>cam end y %f\n", arg->player.cam.end.y);
	int  i = -1;
	// while (++i < X_RES)
	// 	printf("%d : %f %f %f\n", i, arg->rays[i].dir.x, arg->rays[i].dir.y, arg->rays[i].size);
	arg->frame->img = mlx_new_image(arg->mlx, X_RES, Y_RES);
	if (!arg->frame->addr)
		exit(EXIT_FAILURE);
	arg->frame->addr = mlx_get_data_addr(arg->frame->img, &arg->frame->bpp,
			&arg->frame->line_len, &arg->frame->endian);
	arg->frame->path = NULL;
	if (!arg->frame->addr)
		exit(EXIT_FAILURE);
	draw_first_frame(arg);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	mlx_hook(arg->mlx_win, 17, 0, ft_exit_success, arg);
	mlx_key_hook(arg->mlx_win, key_hook, arg);
	mlx_loop(arg->mlx);
}
