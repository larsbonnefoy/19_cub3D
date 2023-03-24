/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:20 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/23 16:58:33 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int set_map(t_map *map, char *line);
int get_id(char *s);
int handle_id(int id, char **tab, t_map *map);
void free_tab(char **tab);
void print_map(t_map *map);
void print_tab(char **tab);
char *replace_endl(char *s);
int is_meta_data(char *line);
int add_map(t_map *map, char *line);

int main(int argc, char **argv)
{
	(void) argc;
	char *line;
	t_map map;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(1, "Error\n", 6);
		return (1);
	}
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);	
		if (!line)
			break;
		if (ft_strncmp(line, "\n", 1) != 0)
			set_map(&map, line);
	}
	map.map = ft_split(map.str_map, '\n');
	printf("---------------\n");
	print_map(&map);
	return (0);
}
/*
 * Map doit tjrs etre en last
 * Le reste peut etre dans n'importe quel ordre
 *		->doit tjrs commencer par l'identifiant
 *		->peut etre separer par pleins d'espaces 
 */
int set_map(t_map *map, char *line)
{
	char **tab_line; 
	int id;
	
	id = is_meta_data(line);
	if (id == -1)
		return (-1);
	if (id)
	{
		tab_line = ft_split(line, ' ');	
		if (!tab_line || tab_line[2] != NULL)
		{
			printf("Error : unvalid meta data");
			return (-1);
		}
		handle_id(id, tab_line, map);
		free_tab(tab_line);
	}
	if (id == 0)
		map->str_map = ft_strjoinf(map->str_map, line);
	return (0);
}

int is_meta_data(char *line)
{
	int i;
	int id;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	id = get_id(line);	
	return (id);
}

/*
 * Returns enum value of id
 */
int get_id(char *s)
{
	if (!s)
		return (-1);
	if (ft_strncmp(s, "NO ", 3) == 0)
		return (NO);
	else if (ft_strncmp(s, "SO ", 3) == 0)
		return (SO);
	else if (ft_strncmp(s, "WE ", 3) == 0)
		return (WE);
	else if (ft_strncmp(s, "EA ", 3) == 0)
		return (EA);
	else if (ft_strncmp(s, "F ", 2) == 0)
		return (F);
	else if (ft_strncmp(s, "C ", 2) == 0)
		return (C);
	else if (ft_strncmp(s, "1", 1) == 0)
		return (0);
	else if (ft_strncmp(s, "0", 1) == 0)
		return (0);
	return (0);
}

int handle_id(int id, char **tab, t_map *map)
{
	char **color;

	color = NULL;
	if ( 0 < id && id < 5 )
	{
		if (id == NO)
			map->NO = replace_endl(ft_strdup(tab[1]));
		else if (id == SO)
			map->SO = replace_endl(ft_strdup(tab[1]));
		else if (id == WE)
			map->WE = replace_endl(ft_strdup(tab[1]));
		else if (id == EA)
			map->EA = replace_endl(ft_strdup(tab[1]));
	}
	else if ( id == 5 || id == 6)
	{
		color = ft_split(tab[1], ',');
		if (!color)
			return (0);
		if (id == F)
		{
			map->F_C[0] = ft_atoi(color[0]);	
			map->F_C[1] = ft_atoi(color[1]);	
			map->F_C[2] = ft_atoi(color[2]);	
		}
		else
		{
			map->C_C[0] = ft_atoi(color[0]);	
			map->C_C[1] = ft_atoi(color[1]);	
			map->C_C[2] = ft_atoi(color[2]);	
		}
		free_tab(color);
	}
	return (1);
}

void free_tab(char **tab)
{
	int i;
	
	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char *replace_endl(char *s)
{
	int i;

	i = 0;
	while(s[i])
	{
		if (s[i] == '\n')
			s[i] = '\0';
		i++;
	}
	return (s);
}

void print_map(t_map *map)
{
	int i;

	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", map->NO, map->SO, map->WE, map->EA);
	printf("F = %d,%d,%d\nC = %d,%d,%d\n", map->F_C[0], map->F_C[1],map->F_C[2],map->C_C[0],map->C_C[1],map->C_C[2]);
	i = 0;
	while(map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
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
