/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnefo <lbonnefo@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:26:30 by lbonnefo          #+#    #+#             */
/*   Updated: 2022/11/09 09:58:51 by lbonnefo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		size;
	int		a;
	int		b;
	char	*str;

	a = -1;
	b = -1;
	size = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((size + 1) * sizeof(char));
	if (str == NULL)
	{	
		free(s1);
		return (NULL);
	}
	while (s1[++a] != '\0')
		str[a] = (char)s1[a];
	free(s1);
	while (s2[++b] != '\0')
		str[a + b] = (char)s2[b];
	str[a + b] = '\0';
	return (str);
}

size_t	ft_strlen(char *s)
{
	size_t	a;

	if (!s)
		return (0);
	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

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

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	srclen;

	a = 0;
	srclen = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (dstsize == 0)
		return (srclen);
	while (src[a] != '\0' && a < dstsize -1)
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (srclen);
}

void	ft_bzero(char *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = '\0';
		i++;
	}
}
