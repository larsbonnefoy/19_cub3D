/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_visualizer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 18:09:31 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/09 15:14:33 by hdelmas          ###   ########.fr       */
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
	// printf("pxl %d %d\n", pxl.x, pxl.y);
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
			set_pixel_color(arg->frame, pixel, 0x0);
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

static void	draw_line(t_ray *line, t_img *frame, unsigned int color)
{
	t_point	vect_dir;
	t_point	pixel;
	t_pixel	pxl;
	int vect_dir_norm;
	double	slope;

	vect_dir.x = line->dir.x;
	vect_dir.y = line->dir.y;
	vect_dir_norm = line->size;
	pixel.x = line->start.x;
	pixel.y = line->start.y;
	printf("1>%d %f %f\n", vect_dir_norm, pixel.x, pixel.y);
	while (vect_dir_norm >= 0)
	{
		pxl.x = round(pixel.x);
		pxl.y = round(pixel.y);
		// printf("%f %f %d %d %d\n", pixel.x, pixel.y, pxl.x, pxl.y, vect_dir_norm);
		set_pixel_color(frame, pxl, color);
		// pixel = goto_next_edge(pixel, line);
		pixel.x += vect_dir.x;
		pixel.y += (vect_dir.y);
		// if (pixel.x < 0)
		// 	pixel.x = 0;
		// if (pixel.y < 0)
		// 	pixel.y = 0;
		--vect_dir_norm;
	}
}

static void	draw_wall(t_arg *arg, t_ray *ray, t_img *frame, int x)
{	 
	int				y;
	double			len_tan_alpha;
	double			y_res_div2;
	double			beta;
	double			p_size;
	t_pixel			pxl;
	unsigned int	color;
	t_point			perp;
	t_point			ppos;
	double		perp_size;

	y = -1;
	
	// beta =  atan(arg->player.cam.dist / sqrt(pow(arg->player.pos.x, 2) + pow(arg->player.pos.y, 2)));
	// p_size = ray->size * sin(beta);
	// beta = 0;
	// if (arg->player.cam.dir.x != 0)
	beta = atan(arg->player.cam.dir.y / arg->player.cam.dir.x);
	perp.x = ray->end.x * cos(beta) + ray->end.y * sin(beta);
	perp.y = -ray->end.x * sin(beta) + ray->end.y * cos(beta);
	ppos.x = arg->player.pos.x * cos(beta) + arg->player.pos.y * sin(beta);
	ppos.y = -arg->player.pos.x * sin(beta) + arg->player.pos.y * cos(beta);
	// p_size = sqrt(pow(perp.x - ppos.x, 2) + pow(perp.y - ppos.y, 2));
	// perp.x = (arg->player.cam.dir.y * ray->end.x) - (arg->player.cam.dir.x * ray->end.y)
	// 	- (arg->player.cam.dir.x
	// 		* ((arg->player.cam.line.y * arg->player.pos.x)
	// 			- (arg->player.cam.line.x * arg->player.pos.y)));
	// perp.y = ((arg->player.cam.line.y * x)
	// 	- (arg->player.cam.line.y * arg->player.pos.x)
	// 	+ (arg->player.cam.line.x * arg->player.pos.y))
	// 		/  arg->player.cam.line.y;
	// p_size = sqrt(pow(perp.x , 2) + pow(perp.y , 2));
	// p_size = fabs(perp.y - arg->player.pos.y);
	p_size = sqrt(pow(perp.x - ppos.x, 2) + pow(perp.y - ppos.y, 2));
	// if (ray->dir.x == 0)
	// 	p_size = perp.y;
	// if (ray->dir.y == 0)
	// 	p_size = perp.x;
	// p_size = ray->size;
	// len_tan_alpha = (Y_RES / 2 - (p_size * tan(ALPHA)));
	y_res_div2 = Y_RES / 2;
	int wall_size = (Y_RES / p_size) * DIV;
	pxl.x = x;
	// printf("%d  %f %f %f %f\n", x,  ray->end.x, ray->end.y, p_size, ray->size);
	while (++y < Y_RES)
	{
		pxl.y = y;
		color = 0xff00ff;
		if (ray->face[0] == 'W')
			color = 0x0000ff;
		if (ray->face[0] == 'N')
			color = 0x00ff00;
		if (ray->face[0] == 'S')
			color = 0xff0000;
		if (ray->face[0] == 'E')
			color = 0xff00ff;
		set_pixel_color(frame, pxl, color);
		if (y < y_res_div2 - wall_size / 2)
			set_pixel_color(frame, pxl, arg->ground_color);
		else if (y > y_res_div2 + wall_size / 2)
			set_pixel_color(frame, pxl, arg->roof_color);
			
	}
}

void	put_walls(t_arg *arg, t_ray *rays)
{
	int			i;
	double		x;
	t_point	ray_pos;
	t_point pos;
	double	line_size;
	
	i = -1;
	ray_pos = arg->player.pos;
	// rays_len(&arg->player, rays, arg->map);
	while (++i < X_RES)
	{
		ray_len(ray_pos, &(rays[i]), arg->map);
		x = 2 * (double)i / ((double)(X_RES) - 1) - 1;
		// pos.x = arg->player.pos.x + arg->player.cam.line.x * x;
		// pos.y = arg->player.pos.y + arg->player.cam.line.y * x;
		// line_size = pow(pos.x - arg->player.pos.x,2) + pow(pos.y - arg->player.pos.y,2);
		// printf(">wall ray size %f %f %f %f\n", rays[i].size, x, pos.x, pos.y);
		rays[i].size = sqrt(pow(rays[i].size, 2) - line_size);
		// printf(">wall ray size %f\n", rays[i].size);
		draw_wall(arg, &(rays[i]), arg->frame, i);
	}
}
void	put_rays(t_arg *arg, t_ray *rays)
{
	int			i;
	t_point	ray_pos;
	unsigned long int	color;
	
	i = -1;
	ray_pos = arg->player.pos;
	while (++i < X_RES)
	{
		color = 0xff00ff;
		ray_len(arg->player.pos, &(rays[i]), arg->map);
		if ((rays[i]).face[0] == 'W')
			color = 0x0000ff;
		if ((rays[i]).face[0] == 'N')
			color = 0x00ff00;
		if ((rays[i]).face[0] == 'S')
			color = 0xff0000;
		if ((rays[i]).face[0] == 'E')
			color = 0xff00ff;
		draw_line(&(rays[i]), arg->frame, color);
	}
}

void	turn(t_arg *arg, double rad)
{
	t_point	rel_cam_prev;
	t_point	rel_line_prev;
	double	csin;
	double	ccos;

	csin = sin(rad);
	ccos = cos(rad);
	rel_cam_prev.x = arg->player.cam.dir.x;
	rel_cam_prev.y = arg->player.cam.dir.y;
	rel_line_prev.x = arg->player.cam.line.x;
	rel_line_prev.y = arg->player.cam.line.y;
	arg->player.cam.dir.x  = rel_cam_prev.x * ccos + rel_cam_prev.y * csin; 
	arg->player.cam.dir.y= -rel_cam_prev.x * csin + rel_cam_prev.y * ccos;
	arg->player.cam.line.x = rel_line_prev.x * ccos + rel_line_prev.y * csin;
	arg->player.cam.line.y = -rel_line_prev.x * csin + rel_line_prev.y * ccos;
}

void	move(t_arg *arg, char *key)
{
	double	cam_dist;
	double	x;
	double	y;
	t_point	pos;
	t_point	vect_cam;

	vect_cam.x = arg->player.cam.dir.x;
	vect_cam.y = arg->player.cam.dir.y;
	cam_dist = sqrt(pow(vect_cam.x , 2) + pow(vect_cam.y, 2));
	vect_cam.x = vect_cam.x;
	vect_cam.y = vect_cam.y;
	// printf(">%f %f\n", vect_cam.x, vect_cam.y);
	if (key[0] == 'w')
	{
		x = vect_cam.x * 10;
		y = vect_cam.y * 10;
	}
	if (key[0] == 's')
	{
		x = -vect_cam.x * 10;
		y = -vect_cam.y * 10;
	}
	if (key[0] == 'a')
	{
		y = -vect_cam.x * 10;
		x = vect_cam.y * 10;
	}
	if (key[0] == 'd')
	{
		y = vect_cam.x * 10;
		x = -vect_cam.y * 10;
	}
	pos.x = x + arg->player.pos.x;
	pos.y = y + arg->player.pos.y;
	if (!in_wall(pos, arg->map))
	{
		arg->player.pos.x += x;
		arg->player.pos.y += y;
		// printf("cam %f %f\n", arg->player.cam.pos.x, arg->player.cam.pos.y);
		// arg->player.cam.pos.x += x;
		// arg->player.cam.pos.y += y;
		// printf(">cam %f %f\n", arg->player.cam.pos.x, arg->player.cam.pos.y);
	}
}

int	key_hook(int keycode, t_arg *arg)
{
	 if (keycode == ESC)
		ft_exit_success(arg);
	if (keycode == W || keycode == UP)
		move(arg, "w");
	if (keycode == S || keycode == DOWN)
		move(arg, "s");
	if (keycode == D)
		move(arg, "d");
	if (keycode == A)
		move(arg, "a");
	if (keycode == RIGHT)
		turn(arg, -PI / 24);
	if (keycode == LEFT)
		turn(arg, PI / 24);
	// printf(">>> HOOK cam dir %f %f cam start %f %f cam end %f %f\n", arg->player.cam.dir.x, arg->player.cam.dir.y, arg->player.cam.start.x, arg->player.cam.start.y, arg->player.cam.end.x, arg->player.cam.end.y);
	draw_first_frame(arg);
	rays_gen(&(arg->player), arg->rays);
	// draw_first_frame(arg);
	// put_rays(arg, arg->rays);
	put_walls(arg, arg->rays);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	// mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->mini->img, 0, 0);
	return (0);
}

void	window(char **map, t_player player, t_ray *rays)
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
	arg->mini = malloc(sizeof(t_img));
	if (!arg->mini)
		exit(EXIT_FAILURE);
	arg->map = map;
	arg->player = player;
	arg->rays = rays;
	arg->ground_color = 0xece75f;
	arg->roof_color = 0x3CB371;
	arg->frame->img = mlx_new_image(arg->mlx, X_RES, Y_RES);
	if (!arg->frame->addr)
		exit(EXIT_FAILURE);
	arg->frame->addr = mlx_get_data_addr(arg->frame->img, &arg->frame->bpp,
			&arg->frame->line_len, &arg->frame->endian);
	arg->frame->path = NULL;
	arg->mini->img = mlx_new_image(arg->mlx, 400, 400);
	if (!arg->mini->addr)
		exit(EXIT_FAILURE);
	arg->mini->addr = mlx_get_data_addr(arg->mini->img, &arg->mini->bpp,
			&arg->mini->line_len, &arg->mini->endian);
	arg->mini->path = NULL;
	if (!arg->mini->addr)
		exit(EXIT_FAILURE);
	draw_first_frame(arg);
	mlx_put_image_to_window(arg->mlx, arg->mlx_win, arg->frame->img, 0, 0);
	mlx_hook(arg->mlx_win, 17, 0, ft_exit_success, arg);
	mlx_key_hook(arg->mlx_win, key_hook, arg);
	mlx_loop(arg->mlx);
}
