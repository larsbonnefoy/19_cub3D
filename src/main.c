/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:12:25 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/13 14:10:53 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycaster.h"
#include "../includes/parsing.h"

void	parsing(int argc, char **argv, t_player *player, t_map *map);

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_ray		rays[X_RES];

	if (argc != 2)
		ft_error("Wrong Number of argumets", 1);
	parsing(argc, argv, &player, &map);
	window(&map, player, rays);
	return (0);
}
