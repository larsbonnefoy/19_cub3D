/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:24:33 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/11/15 08:28:30 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		is_endl(char *str, char *st_chr, int is_buf);
static void		complete_line(char *buf, char *st_chr, int flag);
static int		check_read(int char_read, char *buf, char *st_chr);

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	static char	st_chr[BUFFER_SIZE + 1];
	int			endl;
	char		*next_line;

	if (fd < 0)
		return (NULL);
	next_line = clean_cpy(st_chr);
	if (is_endl(next_line, st_chr, 0) == 1)
		return (next_line);
	endl = 0;
	while (endl == 0)
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		endl = check_read(read(fd, buf, BUFFER_SIZE), buf, st_chr);
		next_line = ft_strjoinf(next_line, buf);
		if (!next_line || (next_line[0] == '\0' && buf[0] == '\0'))
		{	
			free(next_line);
			next_line = NULL;
			return (next_line);
		}	
	}
	return (next_line);
}

int	is_endl(char *buf, char *st_chr, int is_buf)
{
	int	a;

	if (!buf)
		return (1);
	a = 0;
	while (buf[a] != '\0')
	{
		if (buf[a] == '\n')
		{
			if (is_buf == 1)
				complete_line(buf, st_chr, 1);
			return (1);
		}
		a++;
	}
	return (0);
}

void	complete_line(char *buf, char *st_chr, int flag)
{
	int	a;

	a = 0;
	while (buf[a] != '\n' && buf[a] != '\0')
		a++;
	ft_strlcpy(st_chr, buf + a + flag, BUFFER_SIZE + 1);
	ft_strlcpy(buf, buf, ++a + flag);
}

int	check_read(int char_read, char *buf, char *st_chr)
{
	int	a;

	a = -1;
	if (char_read == -1 || char_read == 0)
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		ft_bzero(st_chr, BUFFER_SIZE + 1);
		return (1);
	}
	else if (char_read > 0 && char_read < BUFFER_SIZE)
	{
		while (++a < char_read)
		{	
			if (buf[a] == '\n')
			{
				complete_line(buf, st_chr, 1);
				return (1);
			}
		}
		complete_line(buf, st_chr, 0);
		return (1);
	}			
	return (is_endl(buf, st_chr, 1));
}
