/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:22:14 by lbonnefo          #+#    #+#             */
/*   Updated: 2023/04/13 14:37:28 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	len_tab(char **tab);

char	*del_endl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			s[i] = '\0';
		i++;
	}
	return (s);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_rgb(char **color)
{
	int		i;
	int		j;
	char	*str_color;

	i = 0;
	if (len_tab(color) != 3)
		return (0);
	while (color[i])
	{
		if (i > 2 || ft_strncmp(color[i], "\n", 1) == 0)
			return (0);
		str_color = color[i];
		j = 0;
		while (str_color[j])
		{
			if (!ft_isdigit(str_color[j]) && str_color[j] != '\n')
				return (0);
			j++;
		}	
		i++;
	}
	return (1);
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
