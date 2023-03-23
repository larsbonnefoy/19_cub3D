/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 15:14:01 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/03/23 15:24:03 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
#define PARSING

typedef struct s_map
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		F_R;
	int		F_G;
	int		F_B;
	int		C_R;
	int		C_G;
	int		C_B;
	char	**map;
}	t_map;

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#endif
