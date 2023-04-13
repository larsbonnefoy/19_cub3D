/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:23:22 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/13 10:28:02 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/raycaster.h"

int	ft_exit_success(t_arg *arg)
{
	if (arg)
	{
		if (arg->frame->img)
			mlx_destroy_image(arg->mlx, arg->frame->img);
		if (arg->mlx_win)
			mlx_destroy_window(arg->mlx, arg->mlx_win);
		if (arg->frame)
			free (arg->frame);
		if (arg->no.img)
			mlx_destroy_image(arg->mlx, arg->no.img);
		if (arg->so.img)
			mlx_destroy_image(arg->mlx, arg->so.img);
		if (arg->ea.img)
			mlx_destroy_image(arg->mlx, arg->ea.img);
		if (arg->we.img)
			mlx_destroy_image(arg->mlx, arg->we.img);
		free_tab(arg->map);
		free(arg);
	}
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_exit_error(t_arg *arg)
{
	if (arg)
	{
		if (arg->frame->img)
			mlx_destroy_image(arg->mlx, arg->frame->img);
		if (arg->mlx_win)
			mlx_destroy_window(arg->mlx, arg->mlx_win);
		if (arg->frame)
			free (arg->frame);
		if (arg->no.img)
			mlx_destroy_image(arg->mlx, arg->no.img);
		if (arg->so.img)
			mlx_destroy_image(arg->mlx, arg->so.img);
		if (arg->ea.img)
			mlx_destroy_image(arg->mlx, arg->ea.img);
		if (arg->we.img)
			mlx_destroy_image(arg->mlx, arg->we.img);
		free_tab(arg->map);
		free(arg);
	}
	exit(EXIT_FAILURE);
	return (1);
}
