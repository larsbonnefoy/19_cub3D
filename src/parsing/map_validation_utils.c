/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:08:15 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/06 14:11:07 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_map_char(char c)
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

int	is_map_line(char *line)
{
	int	i;
	int	ret;

	i = 0;
	if (line[0] == '\n')
		return (EMPTY);
	while (line[i])
	{
		ret = is_map_char(line[i]);
		if (ret == MAP_CHAR || ret == PLAYER_CHAR)
			return (ret);
		else if (!ret)
			return (UNVALID);
		i++;
	}
	return (EMPTY_SPACE);
}
