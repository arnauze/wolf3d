/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:00:24 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/01 16:00:25 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

int		keyboard(int key, void *param)
{
	t_variables *d;

	d = param;
	// ft_erase(d);
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_image(d->mlx.mlx, d->mlx.image);
		mlx_destroy_window(d->mlx.mlx, d->mlx.window);
		exit(0);
	}
	else if (key == KEY_W || (key >= KEY_A && key <= KEY_D) ||
    key == KEY_UP || key == KEY_DOWN)
		change_pos(&d->player.position, d, key);
	else if (key == KEY_LEFT || key == KEY_RIGHT)
		angle(&d->player.direction, &d->player.projection_plane, key);
	// else if (key == KEY_DEL)
	// 	reset(d);
    // else if (key == KEY_CTRL_LEFT)
    //     d->player.height = 16;
    // else if (key == KEY_SPACEBAR)
    //     jump(d);
	// ft_draw(d)
	mlx_clear_window(d->mlx.mlx, d->mlx.window);;
	ALGORITHM(d);
	return (0);
}

void		start_modelization(t_variables *data)
{
	data->mlx.mlx = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.mlx, MAX_X, MAX_Y, "Wolf3D");
	data->mlx.image = mlx_new_image(data->mlx.mlx, MAX_X, MAX_Y);
	data->mlx.pixel = (unsigned char*)mlx_get_data_addr(data->mlx.image, &data->mlx.trash_a, &data->mlx.trash_b, &data->mlx.trash_c);
	ALGORITHM(data);
	mlx_hook(data->mlx.window, 2, 3, keyboard, data);
	mlx_loop(data->mlx.mlx);
	// ALGORITHM(data);
}

void		wolf_this_shit(t_variables *data)
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
		wolf_this_shit(data);
	}
	return (0);
}
