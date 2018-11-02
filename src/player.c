/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:52:14 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/01 15:52:17 by amagnan          ###   ########.fr       */
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
}

void	angle(t_vector *d, t_vector *pp, int key)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = d->x;
	old_plane_x = pp->x;
	if (key == KEY_LEFT)
	{
		d->x = d->x * cos(-ROT_SPEED) - d->y * sin(-ROT_SPEED);
		d->y = old_dir_x * sin(-ROT_SPEED) + d->y * cos(-ROT_SPEED);
		pp->x = pp->x * cos(-ROT_SPEED) - pp->y * sin(-ROT_SPEED);
		pp->y = old_plane_x * sin(-ROT_SPEED) + pp->y * cos(-ROT_SPEED);	
	}
	else
	{
		d->x = d->x * cos(ROT_SPEED) - d->y * sin(ROT_SPEED);
		d->y = old_dir_x * sin(ROT_SPEED) + d->y * cos(ROT_SPEED);
		pp->x = pp->x * cos(ROT_SPEED) - pp->y * sin(ROT_SPEED);
		pp->y = old_plane_x * sin(ROT_SPEED) + pp->y * cos(ROT_SPEED);
	}
}

void	change_pos(t_vector *p, t_variables *data, int key)
{
	if (key == KEY_W || key == KEY_UP)
	{		
		if (data->map.map[(int)floor(p->y)][(int)floor(p->x + data->player.direction.x * MOVE_SPEED)] == '0')
			p->x += data->player.direction.x * MOVE_SPEED;
		if (data->map.map[(int)floor(p->y + data->player.direction.y * MOVE_SPEED)][(int)floor(p->x)] == '0')
			p->y += data->player.direction.y * MOVE_SPEED;
	}
	if (key == KEY_S || key == KEY_DOWN)
	{
		if (data->map.map[(int)floor(p->y)][(int)floor(p->x - data->player.direction.x * MOVE_SPEED)] == '0')
			p->x -= data->player.direction.x * MOVE_SPEED;
		if (data->map.map[(int)floor(p->y - data->player.direction.y * MOVE_SPEED)][(int)floor(p->x)] == '0')
			p->y -= data->player.direction.y * MOVE_SPEED;

	}
	if (key == KEY_A)
	{
		if (data->map.map[(int)floor(p->y)][(int)floor(p->x + data->player.direction.y * MOVE_SPEED)] == '0')
			p->x += data->player.direction.y * MOVE_SPEED;
		if (data->map.map[(int)floor(p->y - data->player.direction.x * MOVE_SPEED)][(int)floor(p->x)] == '0')
			p->y -= data->player.direction.x * MOVE_SPEED;
	}
	if (key == KEY_D)
	{
		if (data->map.map[(int)floor(p->y)][(int)floor(p->x - data->player.direction.y * MOVE_SPEED)] == '0')
			p->x -= data->player.direction.y * MOVE_SPEED;
		if (data->map.map[(int)floor(p->y + data->player.direction.x * MOVE_SPEED)][(int)floor(p->x)] == '0')
			p->y += data->player.direction.x * MOVE_SPEED;
	}
}
