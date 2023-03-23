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
	}
	line = NULL;
	while (1)
	{
		line = get_next_line(fd);	
		if (!line)
			break;
		printf("%s\n", line);	
		set_map(&map, line);
	}
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
	int i;
	int id;


	tab_line = ft_split(line, ' ');	
	if (!tab_line)
		return (-1);
	id = get_id(tab_line[0]);
	
	return (0);
}

int get_id(char *s)
{
	if (!s)
		return (-1);
	if (ft_strncmp(s, "NO", 3) == 0)
		return (NO);
	else if (ft_strncmp(s, "SO", 3) == 0)
		return (SO);
	else if (ft_strncmp(s, "WE", 3) == 0)
		return (WE);
	else if (ft_strncmp(s, "EA", 3) == 0)
		return (EA);
	else if (ft_strncmp(s, "F", 2) == 0)
		return (F);
	else if (ft_strncmp(s, "C", 2) == 0)
		return (C);
	return (0);
}

int handle_id(int id, char **tab, t_map *map)
{
	char **color;

	color = NULL;
	if ( 0 < id && id < 5 )
	{
		if (id == NO)
			map->NO = ft_strdup(tab[1]);
		else if (id == SO)
			map->SO = ft_strdup(tab[1]);
		else if (id == WE)
			map->WE= ft_strdup(tab[1]);
		else if (id == EA)
			map->EA= ft_strdup(tab[1]);
	}
	if ( 4 < id && id < 7)
	{
		color = ft_split(tab[1], '\'');
		if (id == F)
		{
				
		}
	
	}
}
