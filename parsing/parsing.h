/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/30 15:55:08 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING_H

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"

#define NB_ID 6

typedef enum e_id
{
	NO = 0,
	SO,
	WE,
	EA,
	F,
	C,
	MAP,
} t_id;

typedef enum e_map_char
{
    UNVALID = 0, 
    MAP_CHAR,
    PLAYER_CHAR,
} t_map_char;

typedef struct s_tmp_pars_info
{
	char	*str_map;
	int		check_id_array[NB_ID];
	char	dir_player;
	int		x_player;
	int		y_player;
	char	*line;
} t_tmp_info;

/*
 * str_map && check_array in function not struct
 */
typedef struct s_map
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int 	F_C[3];
	int 	C_C[3];
	char	**map;
	int		width;
	int 	height;
}	t_map;

int ft_error(char *s, int ret_val);
int pathfinding(t_map *s_map, int start_y, int start_x);
char	*get_next_line(int fd);
#endif
