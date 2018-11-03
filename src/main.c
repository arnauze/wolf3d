/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:00:24 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/03 01:11:03 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void		start_modelization(t_variables *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.mlx, MAX_X, MAX_Y, "Wolf3D");
	data->mlx.image = mlx_new_image(data->mlx.mlx, MAX_X, MAX_Y);
	data->mlx.pixel = (unsigned char*)mlx_get_data_addr(data->mlx.image, &data->mlx.trash_a, &data->mlx.trash_b, &data->mlx.trash_c);
	algorithm(data);
	mlx_hook(data->mlx.window, 2, 0, key_press, data);
	mlx_hook(data->mlx.window, 3, 0, key_release, data);
	mlx_hook(data->mlx.window, 17, 0, key_exit, data);
	mlx_loop_hook(data->mlx.mlx, change_pos, data);
	mlx_loop(data->mlx.mlx);
}

void		wolf(t_variables *data)
{
	init_player(data);
	start_modelization(data);
}

int 		main(int argc, char **argv)
{
	int fd;
	t_variables	*data;

	data = (t_variables *)malloc(sizeof(t_variables));
	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		data->map = get_map(argv[1]);
		wolf(data);
	}
	return (0);
}
