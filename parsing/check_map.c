/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:20 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/30 16:28:18 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int check_valid_line(char *line);
void debug_print_check_array(int check_array[NB_ID]);
int set_map(t_map *map, t_tmp_info *info);
int get_id(char *s);
int handle_id(int id, char **tab, t_map *map);
void free_tab(char **tab);
void print_map(t_map *map, t_tmp_info *info);
void print_tab(char **tab);
char *del_endl(char *s);
int is_meta_data(char *line);
int add_map(t_map *map, char *line);
int ids_done(int check_array[NB_ID]);
int valid_extension(int argc, char **argv);
int	valid_line(t_tmp_info *info, t_map *map);
t_tmp_info	*init_tmp_info();

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
	{
		write(1, "Error\n", 6);
		perror("");
		exit(EXIT_FAILURE);
	}
	valid_extension(argc, argv);
	while (1)
	{
		tmp_info->line = get_next_line(fd);
		if (!tmp_info->line) 
			break;
		set_map(&map, tmp_info);
		free(tmp_info->line);
	}
	if (tmp_info->dir_player == '0')
	{
		printf("No player on the map");
		exit(EXIT_FAILURE);
	}
	printf("---------------\n");
    map.map = ft_split(tmp_info->str_map, '\n'); 
	//free tmp_INFO!!!
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
	{
		printf("Error\nWrong number of argumets provided\n");
		exit(EXIT_FAILURE);
	}	
	len = (int)ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
	{
		printf("Error\nNot a .cub map file\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

/*
 * Map doit tjrs etre en last
 * Le reste peut etre dans n'importe quel ordre
 *		->doit tjrs commencer par l'identifiant
 *		->peut etre separer par pleins d'espaces 
 *	On doit skipper tous les espaces vides tant que check_array n'est pas rempli de 1;
 */
int set_map(t_map *map, t_tmp_info *tmp_info)
{
	int	id;
	char **tmp_tab;

	//debug_print_check_array(check_array);
	if (!ids_done(tmp_info->check_id_array))
	{
		if (ft_strncmp(tmp_info->line, "\n", 1) == 0)
			return (0);
		id = is_meta_data(tmp_info->line);
		if (id < 0 || id == 6) //read map char 
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		if (tmp_info->check_id_array[id] == 0)
			tmp_info->check_id_array[id] = 1;
		else
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		tmp_tab = ft_split(tmp_info->line, ' ');
		if (tmp_tab[2] != NULL && ft_strncmp(tmp_tab[2], "\n", 1) != 0) 
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		handle_id(id, tmp_tab, map);
		free_tab(tmp_tab);
	}
    else if (is_meta_data(tmp_info->line) == MAP)
    {
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
	return (0);
}


int is_map_char(char c)
{
	if (c == '0')
		return (1);
	else if (c == '1')
		return (1);
	else if (c == 'N')
		return (2);
	else if (c == 'S')
		return (2);
	else if (c == 'E')
		return (2);
	else if (c == 'W')
		return (2);
	else if (c == '\n')
		return (1);
	else if (c == ' ')
		return (1);
	else
		return (0);
}

int	valid_line(t_tmp_info *info, t_map *map)
{
	int i;
	int char_type;
	
	i = 0; 
	while(info->line[i])
	{
		char_type = is_map_char(info->line[i]);
		if (!char_type)	
		{
			printf("Unvalid character in map");
			exit(EXIT_FAILURE);
		}
		else if (char_type == 2)
		{
			if (info->dir_player == '0')
			{
				info->dir_player = info->line[i];
				info->x_player = i; 
				info->y_player = map->height - 1;
			}
			else
			{
				printf("Too many players\n");
				exit(EXIT_FAILURE);
			}
		}
		i++;
	}
	return (0);
}


/*
 * on peut mettre le check du \n ici
 */
int is_meta_data(char *line)
{
	int i;
	int id;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == 9) )
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
	else if (ft_strncmp(s, "1", 1) == 0)
		return (MAP);
	else if (ft_strncmp(s, "0", 1) == 0)
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
