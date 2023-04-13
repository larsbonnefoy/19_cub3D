/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:53:18 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/13 10:16:38 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	valid_extension(int argc, char **argv);

t_tmp_info	*init_tmp_info(t_tmp_info *info)
{
	info->str_map = NULL;
	ft_bzero(info->check_id_array, NB_ID * sizeof(int));
	info->dir_player = '0';
	info->x_player = -1;
	info->y_player = -1;
	info->line = NULL;
	info->in_map = 0;
	return (info);
}

int	file_check(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_error((char *)strerror(errno), 1);
	valid_extension(argc, argv);
	return (fd);
}

int	valid_extension(int argc, char **argv)
{
	int	len;

	if (argc != 2)
		ft_error("Wrong number of argumets provided\n", 1);
	len = (int)ft_strlen(argv[1]);
	if (ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		ft_error("Not a .cub map file", 1);
	return (0);
}
