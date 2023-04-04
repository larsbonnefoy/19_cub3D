/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:20:58 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/04 15:58:22 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h> 

static int unvalid_space(char *line, int pos);
int	valid_line(t_tmp_info *info, t_map *map);
void	set_player_info(t_tmp_info *info, int x_pos, int y_pos);

int set_map(t_tmp_info *tmp_info, t_map *map)
{
	if (ft_strncmp(tmp_info->line, "\n", 1) == 0)
	{
		printf("c'est chao = [%s]", tmp_info->line);
		return (0);
	}
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
	return (1);
}

//erreur si 0 ' ' || ' ' 0 || 0 '\n' || '             \n' ||  ( ' ' \n si que ce char la sur la ligne)
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
			ft_error("Unvalid Map", 4);
		else if (char_type == 2)
			set_player_info(info, i, map->height-1);
		i++;
	}
	return (0);
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
		return (NEW_LINE);
	else if (c == ' ')
		return (SPACE);
	else
		return (UNVALID);
}

int is_map_line(char *line)
{
	int i;
	int ret;

	i = 0;
	while (line[i])
	{
		ret = is_map_char(line[i]);
		if (ret == MAP_CHAR || ret == PLAYER_CHAR)
			return (ret);
		else if (!ret)
			return (UNVALID);
		i++;
	}
	return (NOT_MAP_LINE);
}
