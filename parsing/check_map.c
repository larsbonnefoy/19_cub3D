/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:13:20 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/29 15:03:00 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

void debug_print_check_array(int check_array[NB_ID]);
int set_map(t_map *map, char *line, int check_array[NB_ID]);
int get_id(char *s);
int handle_id(int id, char **tab, t_map *map);
void free_tab(char **tab);
void print_map(t_map *map);
void print_tab(char **tab);
char *del_endl(char *s);
int is_meta_data(char *line);
int add_map(t_map *map, char *line);
int ids_done(int check_array[NB_ID]);
int valid_extension(int argc, char **argv);

int main(int argc, char **argv)
{
	(void) argc;
	char *line;
	t_map map;
	int		fd;
	int check_array[NB_ID];

	line = NULL;
	ft_bzero(check_array, NB_ID	* sizeof(int));
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
		line = get_next_line(fd);
		if (!line)
			break;
		set_map(&map, line, check_array);
	}
	printf("---------------\n");
    //map.map = ft_split(map.str_map, '\n'); 
	print_map(&map);
	return (0);
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
int set_map(t_map *map, char *line, int check_array[NB_ID])
{
	int	id;
	char **tmp_tab;

	//debug_print_check_array(check_array);
	if (!ids_done(check_array))
	{
		if (ft_strncmp(line, "\n", 1) == 0)
			return (0);
		id = is_meta_data(line);
		if (id < 0 || id == 6) //read map char 
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		if (check_array[id] == 0)
			check_array[id] = 1;
		else
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		tmp_tab = ft_split(line, ' ');
		if (tmp_tab[2] != NULL && ft_strncmp(tmp_tab[2], "\n", 1) != 0) 
		{
			write(1, "Error\n", 6);
			exit(EXIT_FAILURE);
		}
		handle_id(id, tmp_tab, map);
		free_tab(tmp_tab);
	}
    else if (is_meta_data(line) == MAP)
    {
        if (map->str_map == NULL)
            map->str_map = ft_strdup(line);
        else
            map->str_map = ft_strjoinf(map->str_map, line);
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

void print_map(t_map *map)
{
	//int i;

	printf("NO = %s\nSO = %s\nWE = %s\nEA = %s\n", map->NO, map->SO, map->WE, map->EA);
	printf("F = %d,%d,%d\nC = %d,%d,%d\n", map->F_C[0], map->F_C[1],map->F_C[2],map->C_C[0],map->C_C[1],map->C_C[2]);
	//i = 0;
    printf("%s", map->str_map);
    /*
	while(map->map[i])
	{
		printf("%s\n", map->map[i]);
		i++;
	}
    */
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

