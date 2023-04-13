/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:37:40 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/13 14:23:23 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int		get_id(char *s);
int		handle_id(int id, char **tab, t_map *map);
int		is_meta_data(char *line);
void	handle_color(int id, char **tab, t_map *map);

int	set_meta_data(t_tmp_info *tmp_info, t_map *map)
{
	int		id;
	char	**tmp_tab;

	id = is_meta_data(tmp_info->line);
	if (id == NL)
		return (0);
	if (id < 0 || id == MAP)
		ft_error("Unvalid Meta Data", 1);
	if (tmp_info->check_id_array[id] == 0)
		tmp_info->check_id_array[id] = 1;
	else
		ft_error("Duplicate Meta Data", 1);
	tmp_tab = ft_split(tmp_info->line, ' ');
	if (tmp_tab[1] == NULL || ft_strncmp(tmp_tab[1], "\n", 1) == 0)
		ft_error("Unvalid Meta Data", 2);
	if (tmp_tab[2] != NULL && ft_strncmp(tmp_tab[2], "\n", 1) != 0)
		ft_error("Unvalid Meta Data", 2);
	handle_id(id, tmp_tab, map);
	free_tab(tmp_tab);
	return (1);
}

int	is_meta_data(char *line)
{
	int	i;
	int	id;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	if (line[i] == '\n')
		return (NL);
	line += i;
	id = get_id(line);
	return (id);
}

int	get_id(char *s)
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

int	handle_id(int id, char **tab, t_map *map)
{
	if (0 <= id && id <= 3)
	{
		if (id == NO)
			map->no = del_endl(ft_strdup(tab[1]));
		else if (id == SO)
			map->so = del_endl(ft_strdup(tab[1]));
		else if (id == WE)
			map->we = del_endl(ft_strdup(tab[1]));
		else if (id == EA)
			map->ea = del_endl(ft_strdup(tab[1]));
	}
	else if (id == 4 || id == 5)
		handle_color(id, tab, map);
	return (1);
}

void	handle_color(int id, char **tab, t_map *map)
{
	char	**color;
	int		rgb_val;
	int		i;

	color = ft_split(tab[1], ',');
	if (!is_rgb(color))
		ft_error("Not a valid RGB colour", 1);
	i = 0;
	while (i < 3)
	{
		rgb_val = ft_atoi(color[i]);
		if (rgb_val < 0 || rgb_val > 255)
			ft_error("Not a valid RGB colour", 1);
		if (id == F)
			map->f_c[i] = rgb_val;
		else
			map->c_c[i] = rgb_val;
		i++;
	}
	if (id == F)
		map->floor_c = (map->f_c[0] << 16) | (map->f_c[1] << 8) | map->f_c[2];
	else
		map->ceiling_c = (map->c_c[0] << 16) | (map->c_c[1] << 8) | map->c_c[2];
	free_tab(color);
}
