/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 00:01:05 by hdelmas           #+#    #+#             */
/*   Updated: 2023/04/10 00:01:30 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

int	pressed(int keycode, t_arg *arg)
{
	if (keycode == ESC)
		ft_exit_success(arg);
	if (keycode == W || keycode == UP)
		arg->vertical_vector -= 1;
	if (keycode == S || keycode == DOWN)
		arg->vertical_vector += 1;
	if (keycode == D)
		arg->horizontal_vector += 1;
	if (keycode == A)
		arg->horizontal_vector -= 1;
	if (keycode == RIGHT)
		arg->moment_vector -= 1;
	if (keycode == LEFT)
		arg->moment_vector += 1;
}

int	unpressed(int keycode, t_arg *arg)
{
	if ((keycode == W || keycode == UP))
		arg->vertical_vector += 1;
	if ((keycode == S || keycode == DOWN))
		arg->vertical_vector -= 1;
	if (keycode == D)
		arg->horizontal_vector -= 1;
	if (keycode == A)
		arg->horizontal_vector += 1;
	if (keycode == RIGHT)
		arg->moment_vector += 1;
	if (keycode == LEFT)
		arg->moment_vector -= 1;
}
