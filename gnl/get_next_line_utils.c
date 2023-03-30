/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:26:30 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/11/28 09:14:45 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_cpy(char *st_chr)
{
	int		a;
	int		len;
	char	*next_line;

	len = 0;
	while (st_chr[len] != '\n' && st_chr[len] != '\0')
		len++;
	if (st_chr[len] == '\n')
		len += 1;
	next_line = malloc((len + 1) * sizeof(char));
	if (next_line == NULL)
		return (NULL);
	a = 0;
	while (a < len)
	{
		next_line[a] = st_chr[a];
		a++;
	}
	next_line[a] = '\0';
	ft_strlcpy(st_chr, st_chr + a, BUFFER_SIZE + 1);
	return (next_line);
}
