/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 00:01:05 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/11 11:00:41 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int	pressed(int keycode, t_arg *arg)
{
	printf("pressedkey = %d\n", keycode);
	if (keycode == ESC)
		ft_exit_success(arg);
	if ((keycode == W || keycode == UP) && arg->vertical_vector != -1)
		arg->vertical_vector -= 1;
	if ((keycode == S || keycode == DOWN) && arg->vertical_vector != 1)
		arg->vertical_vector += 1;
	if (keycode == D && arg->horizontal_vector != 1)
		arg->horizontal_vector += 1;
	if (keycode == A && arg->horizontal_vector != -1)
		arg->horizontal_vector -= 1;
	if (keycode == RIGHT && arg->moment_vector != -1)
		arg->moment_vector -= 1;
	if (keycode == LEFT && arg->moment_vector != 1)
		arg->moment_vector += 1;
	return (0);
}

int	unpressed(int keycode, t_arg *arg)
{
	printf("unpressed key = %d\n", keycode);
	if ((keycode == W || keycode == UP))
		arg->vertical_vector = 0;
	if ((keycode == S || keycode == DOWN))
		arg->vertical_vector = 0;
	if (keycode == D)
		arg->horizontal_vector = 0;
	if (keycode == A)
		arg->horizontal_vector = 0;
	if (keycode == RIGHT)
		arg->moment_vector = 0;
	if (keycode == LEFT)
		arg->moment_vector = 0;
	return (0);
}

int	unfocused(int keycode, t_arg *arg)
{
	(void)keycode;
	arg->vertical_vector = 0;
	arg->vertical_vector = 0;
	arg->horizontal_vector = 0;
	arg->horizontal_vector = 0;
	arg->moment_vector = 0;
	arg->moment_vector = 0;
	return (0);
}
