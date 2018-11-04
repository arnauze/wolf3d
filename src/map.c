/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:51:59 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/04 00:36:24 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

int			dont_spawn_mid(t_map map)
{
	if (map.map[map.y / 2][map.x / 2] != '0')
	{
		write(2, "The middle of the map needs ", 28);
		write(2, "to remain empty\n", 16);
		exit(0);
	}
	return (1);
}

void		check_middle(char **map, int count, int i)
{
	if (map[count][i])
	{
		while (map[count][i])
		{
			if (map[count][i] > '1' || map[count][i] < '0')
			{
				ft_putstr_fd("Invalid syntax: Check the characters\n", 2);
				exit(-1);
			}
			i++;
		}
		if (map[count][0] != '1' || map[count][i - 1] != '1')
		{
			ft_putstr_fd("Invalid map: The labyrinth must be surrounded by walls\n", 2);
			exit(-1);
		}
	}
}

int		check_error(char **map, int count, int x)
{
	int		i;

	i = 0;
	if (count == 0 || x == 1)
	{
		if (map[count])
		{
			while (map[count][i])
			{
				if (map[count][i] != '1')
				{
					ft_putstr_fd("Invalid map: The labyrinth must be surrounded by walls\n", 2);
					exit(-1);
				}
				i++;
			}
		}
	}
	else
		check_middle(map, count, i);
	return (1);
}

t_map		get_map(char *path, char *tmp)
{
	int		fd;
	int		fd2;
	int		count;
	t_map	map;

	if ((fd = open(path, O_RDONLY)) == -1 ||
	(fd2 = open(path, O_RDONLY)) == -1 || (count = 0))
		exit(0);
	while (get_next_line(fd, &tmp) > 0 && (++count))
		free(tmp);
	map.map = (char **)malloc(sizeof(char *)* count + 1);
	count = -1;
	while (get_next_line(fd2, &tmp) > 0)
	{
		map.map[++count] = ft_strdup(tmp);
		check_error(map.map, count, 0);
		free(tmp);
	}
	map.map[count + 1] = NULL;
	map.x = ft_strlen(map.map[0]);
	map.y = count + 1;
	if (!(check_error(map.map, count, 1)) || !(map.x = ft_strlen(map.map[0]))
	|| !(map.y = count + 1) || !(dont_spawn_mid(map)) || (close(fd)) || (close(fd2)))
		exit(0);
	return (map);
}
