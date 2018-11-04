/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: feedme  <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:52:14 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/03 13:41:25 by feedme           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void	init_player(t_variables *data)
{
	data->player.position.x = (double)data->map.x / 2 - 0.5;
	data->player.position.y = (double)data->map.y / 2 - 0.5;
	data->player.direction.x = 1;
	data->player.direction.y = 0;
	data->player.projection_plane.x = 0;
	data->player.projection_plane.y = 0.66;
	data->player.sprint = 1;
}

void	forward_back(t_variables *data)
{
	if (data->move.up == 1)
	{
		if (data->map.map[(int)floor(data->player.position.y)]
		[(int)floor(data->player.position.x + data->player.direction.x * MOVE_SPEED * data->player.sprint)] == '0')
			data->player.position.x += data->player.direction.x * MOVE_SPEED * data->player.sprint;
		if (data->map.map[(int)floor(data->player.position.y +
		data->player.direction.y * MOVE_SPEED * data->player.sprint)][(int)floor(data->player.position.x)] == '0')
			data->player.position.y += data->player.direction.y * MOVE_SPEED * data->player.sprint;
	}
	else if (data->move.down == 1)
	{
		if (data->map.map[(int)floor(data->player.position.y)]
		[(int)floor(data->player.position.x - data->player.direction.x * MOVE_SPEED * data->player.sprint)] == '0')
			data->player.position.x -= data->player.direction.x * MOVE_SPEED * data->player.sprint;
		if (data->map.map[(int)floor(data->player.position.y -
		data->player.direction.y * MOVE_SPEED * data->player.sprint)][(int)floor(data->player.position.x)] == '0')
			data->player.position.y -= data->player.direction.y * MOVE_SPEED * data->player.sprint;
	}
}

void	strafe(t_variables *data)
{
	if (data->move.left == 1)
	{
		if (data->map.map[(int)floor(data->player.position.y)]
		[(int)floor(data->player.position.x + data->player.direction.y * MOVE_SPEED * data->player.sprint)] == '0')
			data->player.position.x += data->player.direction.y * MOVE_SPEED * data->player.sprint;
		if (data->map.map[(int)floor(data->player.position.y -
		data->player.direction.x * MOVE_SPEED * data->player.sprint)][(int)floor(data->player.position.x)] == '0')
			data->player.position.y -= data->player.direction.x * MOVE_SPEED * data->player.sprint;
	}
	else if (data->move.right == 1)
	{
		if (data->map.map[(int)floor(data->player.position.y)]
		[(int)floor(data->player.position.x - data->player.direction.y * MOVE_SPEED * data->player.sprint)] == '0')
			data->player.position.x -= data->player.direction.y * MOVE_SPEED * data->player.sprint;
		if (data->map.map[(int)floor(data->player.position.y +
		data->player.direction.x * MOVE_SPEED * data->player.sprint)][(int)floor(data->player.position.x)] == '0')
			data->player.position.y += data->player.direction.x * MOVE_SPEED * data->player.sprint;
	}
}

void	rotate_left(t_variables *data, double dir0, double pp0)
{
	if (data->move.rotate_left == 1)
	{
		data->player.direction.x = data->player.direction.x *
			cos(-ROT_SPEED) - data->player.direction.y * sin(-ROT_SPEED);
		data->player.direction.y = dir0 * sin(-ROT_SPEED) +
			data->player.direction.y * cos(-ROT_SPEED);
		data->player.projection_plane.x = data->player.projection_plane.x *
			cos(-ROT_SPEED) - data->player.projection_plane.y * sin(-ROT_SPEED);
		data->player.projection_plane.y = pp0 * sin(-ROT_SPEED) +
			data->player.projection_plane.y * cos(-ROT_SPEED);
	}
}

int		change_pos(t_variables *data)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.direction.x;
	old_plane_x = data->player.projection_plane.x;
	forward_back(data);
	strafe(data);
	rotate_left(data, old_dir_x, old_plane_x);
	if (data->move.rotate_right == 1)
	{
		data->player.direction.x = data->player.direction.x *
			cos(ROT_SPEED) - data->player.direction.y * sin(ROT_SPEED);
		data->player.direction.y  = old_dir_x * sin(ROT_SPEED) +
			data->player.direction.y * cos(ROT_SPEED);
		data->player.projection_plane.x = data->player.projection_plane.x *
			cos(ROT_SPEED) - data->player.projection_plane.y * sin(ROT_SPEED);
		data->player.projection_plane.y = old_plane_x * sin(ROT_SPEED) +
			data->player.projection_plane.y * cos(ROT_SPEED);
	}
	algorithm(data);
	return (0);
}
