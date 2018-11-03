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

// int		keyboard(int key, void *param)
// {
// 	t_variables *d;

// 	d = param;
// 	// ft_erase(d);
// 	if (key == KEY_ESCAPE)
// 	{
// 		mlx_destroy_image(d->mlx.mlx, d->mlx.image);
// 		mlx_destroy_window(d->mlx.mlx, d->mlx.window);
// 		exit(0);
// 	}
// 	if (key == KEY_W || (key >= KEY_A && key <= KEY_D) ||
//     key == KEY_UP || key == KEY_DOWN)
// 		change_pos(&d->player.position, d, key);
// 	if (key == KEY_LEFT || key == KEY_RIGHT)
// 		angle(&d->player.direction, &d->player.projection_plane, key);
// 	// else if (key == KEY_DEL)
// 	// 	reset(d);
//     // else if (key == KEY_CTRL_LEFT)
//     //     d->player.crouch = (d->player.crouch) ? 0 : 1;
//     // else if (key == KEY_SPACEBAR)
//     //     jump(d);
// 	// ft_draw(d)
// 	mlx_clear_window(d->mlx.mlx, d->mlx.window);;
// 	algorithm(d);
// 	return (0);
// }

int 		key_release(int key, void *param)
{
	t_variables *data;

	data = (t_variables*)param;
	if (key == KEY_W || key == KEY_UP)
		data->move.up = 0;
	if (key == KEY_DOWN || key == KEY_S)
		data->move.down = 0;
	if (key == KEY_A)
		data->move.left = 0;
	if (key == KEY_D)
		data->move.right = 0;
	if (key == KEY_RIGHT)
		data->move.rotate_right = 0;
	if (key == KEY_LEFT)
		data->move.rotate_left = 0;
	return (0);
}

int 		key_press(int key, void *param)
{
	t_variables *data;

	data = (t_variables*)param;
	if (key == KEY_ESCAPE)
	{
		mlx_destroy_image(data->mlx.mlx, data->mlx.image);
		mlx_destroy_window(data->mlx.mlx, data->mlx.window);
		exit(0);
	}
	if (key == KEY_W || key == KEY_UP)
	{
		data->move.up = 1;
		data->move.down = 0;
	}
	if (key == KEY_DOWN || key == KEY_S)
	{
		data->move.up = 0;
		data->move.down = 1;
	}
	if (key == KEY_A)
	{
		data->move.left = 1;
		data->move.right = 0;
	}
	if (key == KEY_D)
	{
		data->move.right = 1;
		data->move.left = 0;
	}
	if (key == KEY_RIGHT)
	{
		data->move.rotate_right = 1;
		data->move.rotate_left = 0;
	}
	if (key == KEY_LEFT)
	{
		data->move.rotate_right = 0;
		data->move.rotate_left = 1;
	}
	return (0);
}

int 		key_exit(void)
{
	exit(0);
	return (0);
}

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
