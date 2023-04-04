/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:37:40 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/04 15:21:28 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int get_id(char *s);
static char *del_endl(char *s);
static int handle_id(int id, char **tab, t_map *map);
int is_meta_data(char *line);

int set_meta_data(t_tmp_info *tmp_info, t_map *map)
{
	int id;
	char **tmp_tab;

	if (ft_strncmp(tmp_info->line, "\n", 1) == 0)
		return (0);
	id = is_meta_data(tmp_info->line);
	if (id < 0 || id == MAP) //read map char 
		ft_error("Unvalid Meta Data", 1);
	if (tmp_info->check_id_array[id] == 0)
		tmp_info->check_id_array[id] = 1;
	else
		ft_error("Duplicate Meta Data", 1);
	tmp_tab = ft_split(tmp_info->line, ' ');
	if (tmp_tab[2] != NULL && ft_strncmp(tmp_tab[2], "\n", 1) != 0) 
		ft_error("Unvalid Meta Data", 2);
	handle_id(id, tmp_tab, map);
	free_tab(tmp_tab);
	return (1);
}

/*
 * on peut mettre le check du \n ici
 */
int is_meta_data(char *line)
{
	int i;
	int id;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	line += i;
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
	else if (is_map_char(s[0]) != 0)
		return (MAP);
    return (-1);
}

int handle_id(int id, char **tab, t_map *map)
{
	char **color;

	color = NULL;
	if ( 0 <= id && id <= 3 )
	{
		if (id == NO)
			map->NO = del_endl(ft_strdup(tab[1]));
		else if (id == SO)
			map->SO = del_endl(ft_strdup(tab[1]));
		else if (id == WE)
			map->WE = del_endl(ft_strdup(tab[1]));
		else if (id == EA)
			map->EA = del_endl(ft_strdup(tab[1]));
	}
	else if ( id == 4 || id == 5)
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

char *del_endl(char *s)
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
