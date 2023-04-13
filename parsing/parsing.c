/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmas <hdelmas@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:20 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/13 09:17:27 by hdelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "../raycasting/raycaster.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int			set_map(t_tmp_info *tmp_info, t_map *map);
int			ids_done(int check_array[NB_ID]);
void		set_data(t_map *map, t_tmp_info *info);
void		print_map(t_map *map);
int			valid_extension(int argc, char **argv);
t_tmp_info	*init_tmp_info(t_tmp_info *info);
void		init_player(t_player *player, t_tmp_info *tmp_info);
void		parsing(int argc, char **argv, t_player *player, t_map *map);
void		free_parsing_structs(t_map *map);
int			file_check(int argc, char **argv);

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;
	t_ray		rays[X_RES];

	parsing(argc, argv, &player, &map);
	print_map(&map);
	window(&map, player, rays);
	free_parsing_structs(&map);
	return (0);
}

void	free_parsing_structs(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
	free_tab(map->map);
}

void	parsing(int argc, char **argv, t_player *player, t_map *map)
{
	t_tmp_info	*tmp_info;
	int			fd;

	map->height = 0;
	fd = file_check(argc, argv);
	tmp_info = malloc(sizeof(t_tmp_info));
	if (!tmp_info)
		ft_error("Could not allocate memory", 1);
	init_tmp_info(tmp_info);
	while (1)
	{
		tmp_info->line = get_next_line(fd);
		if (!tmp_info->line)
			break ;
		set_data(map, tmp_info);
		free(tmp_info->line);
	}
	map->map = ft_split(tmp_info->str_map, '\n');
	map_validation(map, tmp_info);
	if (tmp_info->dir_player == '0')
		ft_error("No player on the map", 1);
	init_player(player, tmp_info);
	free(tmp_info->str_map);
	free(tmp_info);
}

int	file_check(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error((char *)strerror(errno), 1);
	valid_extension(argc, argv);
	return (fd);
}

void	init_player(t_player *player, t_tmp_info *tmp_info)
{
	player->pos.x = (double)tmp_info->x_player * DIV + (DIV / 2);
	player->pos.y = (double)tmp_info->y_player * DIV + (DIV / 2);
	set_dir(player, tmp_info->dir_player);
}

/*
 * Quand on voit un char N S W E 0 1 on est dans la map
 * =>plus le droit au \n seuls ou a une ligne avec que des espaces
 */
void	set_data(t_map *map, t_tmp_info *tmp_info)
{
	int	ret;

	if (!ids_done(tmp_info->check_id_array))
		set_meta_data(tmp_info, map);
	else
	{
		ret = is_map_line(tmp_info->line);
		if ((ret == EMPTY && tmp_info->in_map == 1) || !ret)
			ft_error("Unvalid Map", 3);
		if ((ret == EMPTY || ret == EMPTY_SPACE) && tmp_info->in_map == 0)
			return ;
		if ((ret == MAP_CHAR || ret == PLAYER_CHAR) && tmp_info->in_map == 0)
			tmp_info->in_map = 1;
		set_map(tmp_info, map);
	}
}

int	set_map(t_tmp_info *tmp_info, t_map *map)
{
	map->height += 1;
	if (tmp_info->str_map == NULL)
	{
		map->width = (int)ft_strlen(tmp_info->line) - 1;
		tmp_info->str_map = ft_strdup(tmp_info->line);
	}
	else
	{
		tmp_info->str_map = ft_strjoinf(tmp_info->str_map, tmp_info->line);
		if ((int)ft_strlen(tmp_info->line) - 1 > map->width)
			map->width = ft_strlen(tmp_info->line) - 1;
	}
	return (1);
}

t_tmp_info	*init_tmp_info(t_tmp_info *info)
{
	info->str_map = NULL;
	ft_bzero(info->check_id_array, NB_ID * sizeof(int));
	info->dir_player = '0';
	info->x_player = -1;
	info->y_player = -1;
	info->line = NULL;
	info->in_map = 0;
	return (info);
}

int	valid_extension(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		ft_error("Wrong number of argumets provided\n", 1);
	len = (int)ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		ft_error("Not a .cub map file", 1);
	return (0);
}

void	print_map(t_map *map)
{
	int	i;

	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", map->no, map->so, map->we, map->ea);
	printf("F = %d,%d,%d\nC = %d,%d,%d\n", map->F_C[0], map->F_C[1],map->F_C[2],map->C_C[0],map->C_C[1],map->C_C[2]);
	printf("Fhex = %X\nChex = %X\n", map->floor_c, map->ceiling_c);
	i = 0;
	while(map->map[i])
	{
		printf("%d	|%s|\n",i , map->map[i]);
		i++;
	}
	printf("width = %d, height = %d\n", map->width, map->height);
}

int	ids_done(int check_array[NB_ID])
{
	int	i;

	i = 0;
	while (i < NB_ID)
	{
		if (check_array[i] == 0)
			return (0);
		i++;
	}
	return (1);
}
