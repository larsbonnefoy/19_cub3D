/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:20 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/03 16:02:35 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

int check_valid_line(char *line);
int ids_done(int check_array[NB_ID]);
void debug_print_check_array(int check_array[NB_ID]);
int set_data(t_map *map, t_tmp_info *info);
int get_id(char *s);
void print_map(t_map *map, t_tmp_info *info);
void print_tab(char **tab);
int valid_extension(int argc, char **argv);
int	valid_line(t_tmp_info *info, t_map *map);
t_tmp_info	*init_tmp_info();

/*
 * init both struct
 */
int main(int argc, char **argv)
{
	(void) argc;
	t_map map;
	int		fd;
	t_tmp_info *tmp_info;

	map.height = 0;
	tmp_info = malloc(sizeof(t_tmp_info));
	init_tmp_info(tmp_info);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
        ft_error((char *)strerror(errno), 1);
	valid_extension(argc, argv);
	while (1)
	{
		tmp_info->line = get_next_line(fd);
		if (!tmp_info->line) 
			break;
		set_data(&map, tmp_info);
		free(tmp_info->line);
	}
    //is on met un joueur en y == 0 on a quand meme cette erreur
	if (tmp_info->dir_player == '0')
        ft_error("No player on the map", 1);
	printf("---------------\n");
    map.map = ft_split(tmp_info->str_map, '\n'); 
	//free tmp_INFO!!!
    pathfinding(&map, tmp_info->y_player, tmp_info->x_player);
	print_map(&map, tmp_info);
	return (0);
}

t_tmp_info	*init_tmp_info(t_tmp_info *info)
{
	info->str_map = NULL;
	ft_bzero(info->check_id_array, NB_ID *sizeof(int));
	info->dir_player = '0';
	info->x_player = -1;
	info->y_player = -1;
	info->line = NULL;
	return (info);
}

int valid_extension(int argc, char **argv)
{
	int	len;

	if (argc != 2)
        ft_error("Wrong number of argumets provided\n", 1);
	len = (int)ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
        ft_error("Not a .cub map file", 1);
	return (0);
}

/*
 * Map doit tjrs etre en last
 * Le reste peut etre dans n'importe quel ordre
 *		->doit tjrs commencer par l'identifiant
 *		->peut etre separer par pleins d'espaces 
 *	On doit skipper tous les espaces vides tant que check_array n'est pas rempli de 1;
 */
int set_data(t_map *map, t_tmp_info *tmp_info)
{
	if (!ids_done(tmp_info->check_id_array))
		set_meta_data(tmp_info, map);
    else if (is_meta_data(tmp_info->line) == MAP)
    {
		if (ft_strncmp(tmp_info->line, "\n", 1) == 0)
			return (0);
		map->height += 1;
		valid_line(tmp_info, map);
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
	}
	else
		ft_error("Unvalid Map", 3);
	return (0);
}

int is_map_char(char c)
{
	if (c == '0')
		return (MAP_CHAR);
	else if (c == '1')
		return (MAP_CHAR);
	else if (c == 'N')
		return (PLAYER_CHAR);
	else if (c == 'S')
		return (PLAYER_CHAR);
	else if (c == 'E')
		return (PLAYER_CHAR);
	else if (c == 'W')
		return (PLAYER_CHAR);
	else if (c == '\n')
		return (MAP_CHAR);
	else if (c == ' ')
		return (MAP_CHAR);
	else
		return (UNVALID);
}

void	set_player_info(t_tmp_info *info, int x_pos, int y_pos)
{
	if (info->dir_player == '0')
	{
		info->dir_player = info->line[x_pos];
		info->x_player = x_pos; 
		info->y_player = y_pos;
	}
	else
		ft_error("Too many players\n", 1);
}

int unvalid_space(char *line, int pos)
{
	char cur;
	char next;

	cur = line[pos];
	next = line[pos + 1];
	if (cur == '0' && next == ' ')
		return (1);
	else if (cur == ' ' && next == '0')
		return (1);
	else if (cur == '0' && next == '\n')
		return (1);
	return (0);
}

//erreur si 0 ' ' || ' ' 0 || 0 '\n' || ( ' ' \n si que ce char la sur la ligne)
int	valid_line(t_tmp_info *info, t_map *map)
{
	int i;
	int char_type;
	
	i = 0; 
	while(info->line[i])
	{
		char_type = is_map_char(info->line[i]);
		if (char_type == UNVALID)
            ft_error("Unvalid character in map", 1);
		else if (unvalid_space(info->line, i))
			ft_error("Invalid Map", 1);
		else if (char_type == 2)
			set_player_info(info, i, map->height-1);
		i++;
	}
	return (0);
}

void print_map(t_map *map, t_tmp_info *info)
{
	int i;

	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", map->NO, map->SO, map->WE, map->EA);
	printf("F = %d,%d,%d\nC = %d,%d,%d\n", map->F_C[0], map->F_C[1],map->F_C[2],map->C_C[0],map->C_C[1],map->C_C[2]);
	i = 0;
	while(map->map[i])
	{
		printf("%d	|%s|\n",i , map->map[i]);
		i++;
	}
	printf("width = %d, height = %d\n", map->width, map->height);
	printf("player dir = %c,  x_player = %d, y_player  = %d\n", info->dir_player, info->x_player, info->y_player);
}

void print_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		printf("%s\n",tab[i]);
		i++;
	}
}

int ids_done(int check_array[NB_ID])
{
	int i;

	i = 0;
	while (i < NB_ID)
	{
		if (check_array[i] == 0)
			return (0);	
		i++;
	}
	return (1);
}

void debug_print_check_array(int check_array[NB_ID])
{
	int i;

	i = 0;
	while (i < NB_ID)
	{
		printf("%d", check_array[i]);
		i++;
	}
	printf("\n");
}
