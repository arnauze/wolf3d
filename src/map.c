/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:51:59 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/01 15:52:08 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

t_map		get_map(char *path)
{
	char	*tmp;
	int		fd;
	int		fd2;
	int		count;
	t_map	map;

	count = 0;
	fd = open(path, O_RDONLY);
	fd2 = open(path, O_RDONLY);
	while (get_next_line(fd, &tmp) > 0)
	{
		free(tmp);
		count++;
	}
	map.map = (char **)malloc(sizeof(char *)* count + 1);
	count = -1;
	while (get_next_line(fd2, &tmp) > 0)
	{
		map.map[++count] = ft_strdup(tmp);
		free(tmp);
	}
	map.map[count + 1] = NULL;
	map.x = ft_strlen(map.map[0]);
	map.y = count + 1;
	close(fd);
	close(fd2);
	return (map);
}
