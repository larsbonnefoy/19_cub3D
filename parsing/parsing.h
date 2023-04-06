/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/06 14:23:45 by lbonnefo         ###   ########.fr       */
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
	NL,
} t_id;

typedef enum e_map_char
{
	EMPTY_SPACE = -1,
    UNVALID, 
    MAP_CHAR,
    PLAYER_CHAR,
	NEW_LINE,
	SPACE,
	EMPTY,
} t_map_char;

typedef struct s_tmp_pars_info
{
	char	*str_map;
	int		check_id_array[NB_ID];
	char	dir_player;
	int		x_player;
	int		y_player;
	int		in_map;
	char	*line;
} t_tmp_info;

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

typedef struct s_check_line
{
	char *curr_line;
	int	curr_i;
	char *next_line;
	int	len_next;
	int len_prev;
} t_check_line; 

//map_validation.c
void map_validation(t_map *map, t_tmp_info *tmp_info);
//map_validation_utils.c
int is_map_char(char c);
int is_map_line(char *line);
//check_id.c
int set_meta_data(t_tmp_info *tmp_info, t_map *map);
//check_id_utils.c
char	*del_endl(char *s);
void	free_tab(char **tab);
//
int ft_error(char *s, int ret_val);
char	*get_next_line(int fd);
#endif