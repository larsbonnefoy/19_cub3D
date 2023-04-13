/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 08:57:56 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/06 14:10:50 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int		valid_pos(int curr_x, int curr_y, t_check_line *s_line, t_map *map);
void	set_player_info(t_tmp_info *info, int x_pos, int y_pos, char *line);
int		valid_line(t_map *map, t_tmp_info *info, t_check_line *s_line);
int		is_valid_space(t_check_line *s_line, int curr_x);

void	map_validation(t_map *map, t_tmp_info *tmp_info)
{
	int				curr_line;
	t_check_line	s_line;

	curr_line = 0;
	s_line.len_prev = 0;
	while (curr_line < map->height)
	{
		s_line.curr_line = map->map[curr_line];
		s_line.curr_i = curr_line;
		if (curr_line > 0)
			s_line.len_prev = ft_strlen(map->map[curr_line - 1]);
		if (curr_line == map->height - 1)
			s_line.next_line = NULL;
		else
		{
			s_line.next_line = map->map[curr_line + 1];
			s_line.len_next = ft_strlen(s_line.next_line);
		}
		valid_line(map, tmp_info, &s_line);
		curr_line++;
	}
}

int	valid_line(t_map *map, t_tmp_info *info, t_check_line *s_line)
{
	char	curr_char;
	int		i;

	i = 0;
	while (s_line->curr_line[i])
	{
		curr_char = is_map_char(s_line->curr_line[i]);
		if (!curr_char)
			ft_error("Unvalid char on map", 1);
		else if (s_line->curr_line[i] != '1')
		{
			if (!valid_pos(i, s_line->curr_i, s_line, map))
				ft_error("Unvalid map", 2);
			if (curr_char == PLAYER_CHAR)
				set_player_info(info, i, s_line->curr_i, s_line->curr_line);
		}
		i++;
	}
	return (0);
}

int	valid_pos(int curr_x, int curr_y, t_check_line *s_line, t_map *map)
{
	char	next_char;

	if (s_line->curr_line[curr_x] == ' ')
	{
		if (!is_valid_space(s_line, curr_x))
			return (0);
	}
	else
	{
		next_char = s_line->curr_line[curr_x + 1];
		if (curr_x == 0 || curr_y == 0 || curr_y == map->height - 1)
			return (0);
		else if (next_char == '\0' || next_char == ' ')
			return (0);
		else if (s_line->len_prev <= curr_x || s_line->len_next <= curr_x)
			return (0);
		if (s_line->next_line && s_line->len_next > curr_x)
		{
			next_char = s_line->next_line[curr_x];
			if (next_char == ' ')
				return (0);
		}
	}
	return (1);
}

int	is_valid_space(t_check_line *s_line, int curr_x)
{
	if (s_line->next_line && s_line->len_next > curr_x)
	{
		if (is_map_char(s_line->next_line[curr_x]) == PLAYER_CHAR)
			return (0);
		if (s_line->next_line[curr_x] == '0')
			return (0);
	}
	if (is_map_char(s_line->curr_line[curr_x + 1]) == PLAYER_CHAR)
		return (0);
	if (s_line->curr_line[curr_x + 1] == '0')
		return (0);
	return (1);
}

void	set_player_info(t_tmp_info *info, int x_pos, int y_pos, char *line)
{
	if (info->dir_player == '0')
	{
		info->dir_player = line[x_pos];
		info->x_player = x_pos;
		info->y_player = y_pos;
	}
	else
		ft_error("Too many players\n", 1);
}
