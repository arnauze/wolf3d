/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 20:49:16 by amagnan           #+#    #+#             */
/*   Updated: 2018/10/25 20:49:17 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				read_until_line(const int fd, char **tab, char **save, char *str)
{
	char			*tmp;
	char			*new;
	size_t			i;

	i = 0;
	(tab[fd]) ? ft_strdel(&tab[fd]) : 0;
	if (*save)
	{
		new = ft_strdup(*save);
		ft_strdel(save);
	}
	else
		new = ft_strdup("");
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_strsub(str, 0, i);
	*save = ft_strjoin(new, tmp);
	ft_strdel(&new);
	ft_strdel(&tmp);
	if (i < ft_strlen(str) - 1)
	{
		tab[fd] = ft_strsub(str, i + 1, ft_strlen(str));
		return (-1);
	}
	return (1);
}

static int				read_line(const int fd, char **tab, char **line, char **save)
{
	int				x;
	char			buf[BUFF_SIZE + 1];

	while ((x = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[x] = '\0';
		if (read_until_line(fd, tab, save, buf) == -1)
			break ;
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (*save)
	{
		*line = ft_strdup(*save);
		ft_strdel(save);
	}
	return (x);
}

static int				check_for_line(const int fd, char **tab, char **save, char *str)
{
	char			*tmp;
	size_t			i;

	tmp = ft_strdup(str);
	ft_strdel(&str);
	if (tmp[0] == '\n')
	{
		*save = ft_strdup("");
		tab[fd] = ft_strsub(tmp, 1, ft_strlen(tmp));
		ft_strdel(&tmp);
		return (-1);
	}
	else
	{
		i = 0;
		while (tmp[i] && tmp[i] != '\n')
			i++;
		*save = ft_strsub(tmp, 0, i);
		i++;
		if (tmp[i] && i < ft_strlen(tmp))
		{
			tab[fd] = ft_strsub(tmp, i, ft_strlen(tmp));
			ft_strdel(&tmp);
			return (-1);
		}
		tab[fd] = ft_strdup("");
		ft_strdel(&tmp);
		return (1);
	}
}

int					get_next_line(const int fd, char **line)
{
	static char		*tab[4864];
	char			*save;
	int				x;

	save = NULL;
	if (!*line)
		*line = ft_strnew(BUFF_SIZE);
	else
		ft_bzero(*line, ft_strlen(*line));
	if (tab[fd])
	{
		if (check_for_line(fd, tab, &save, tab[fd]) == -1)
		{
			*line = ft_strdup(save);
			ft_strdel(&save);
			return (1);
		}
	}
	x = read_line(fd, tab, line, &save);
	if (x > 0 || (x == 0 && *line[0]))
		return (1);
	return (0);
}