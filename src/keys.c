/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 00:59:00 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/03 00:59:02 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

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
