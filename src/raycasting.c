/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:51:45 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/01 15:51:46 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

void ALGORITHM(t_variables *data)
{
	/*

			[	while (x < 5120)
					x = x + 4; 		]
			Loop in every column of the plane
			First find the wall using the 2D map coordinates as pixels by multiplying by 64 (BLOCK_SIZE)
			Find coordinates of intersections and find the closest intersection
			Calculate the size in pixels based on the distance from the player
			Draw the column and increment your x by 4 to go to the next pixel then start again
	*/
	double 	x = 0;
	int 	hit;
	double	line_height;
	t_color	color;

	color.B = 146;
	color.A = 0;
	color.G = 145;
	color.R = 131;
	new_frame(data->mlx.pixel, 5120 * MAX_Y);
	while (x < 5120)
	{
		hit = 0;
		// Initialize variables
		data->camera = 2.0 * (x / 4.0) / MAX_X - 1.0; // To calculate the angle
		data->ray.x = data->player.direction.x + data->player.projection_plane.x * data->camera;
		data->ray.y = data->player.direction.y + data->player.projection_plane.y * data->camera;

		data->ray.map.x = floor(data->player.position.x);
		data->ray.map.y = floor(data->player.position.y);
		data->ray.delta_dist.x = sqrt((data->ray.y * data->ray.y) / (data->ray.x * data->ray.x) + 1.0);//fabs(1 / data->ray.x);
		data->ray.delta_dist.y = sqrt((data->ray.x * data->ray.x) / (data->ray.y * data->ray.y) + 1.0);//fabs(1 / data->ray.y);
		// Calculate step and initial sideDist
		data->ray.step.x = (data->ray.x < 0 ? -1 : 1);
		data->ray.step.y = (data->ray.y < 0 ? -1 : 1);
		data->ray.dist_side.x = (data->ray.x < 0 ? data->player.position.x - data->ray.map.x : data->ray.map.x + 1.0 - data->player.position.x) * data->ray.delta_dist.x;
		data->ray.dist_side.y = (data->ray.y < 0 ? data->player.position.y - data->ray.map.y : data->ray.map.y + 1.0 - data->player.position.y) * data->ray.delta_dist.y;
		// Perform DDA / Find the closest wall by casting the rays
		while (hit == 0)
		{
			// Jump to next map square wethere in X-direction or in Y-direction, depending on which one's the closest
			if (data->ray.dist_side.x < data->ray.dist_side.y)
			{
				data->ray.dist_side.x += data->ray.delta_dist.x;
				data->ray.map.x += data->ray.step.x;
				data->ray.side = 0;
			}
			else
			{
				data->ray.dist_side.y += data->ray.delta_dist.y;
				data->ray.map.y += data->ray.step.y;
				data->ray.side = 1;
			}
			if (data->ray.map.x < 0 || data->ray.map.y < 0 || data->ray.map.x >= data->map.x || data->ray.map.y >= data->map.y)
				break ;
			if (data->map.map[(int)floor(data->ray.map.y)][(int)floor(data->ray.map.x)] > '0')
				hit = 1;
		}
		// Calculate the distance projected on the projection plane
		data->distance = (data->ray.side ? (data->ray.map.y - data->player.position.y + (1.0 - data->ray.step.y) / 2.0) / data->ray.y : (data->ray.map.x - data->player.position.x + (1.0 - data->ray.step.x) / 2.0) / data->ray.x);
		// Calculate line_height on projection plane
		line_height = MAX_Y / data->distance;
		if (line_height > 780)
			line_height = 780;
		if (line_height < 0)
			line_height = 0;
		put_column(data->mlx.pixel, x, line_height, color);
		x += 4;
	}
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.window, data->mlx.image, 0, 0);
}
