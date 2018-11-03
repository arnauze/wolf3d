/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amagnan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 15:54:17 by amagnan           #+#    #+#             */
/*   Updated: 2018/11/01 15:54:19 by amagnan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/wolf3d.h"

t_color		get_color(t_variables *data)
{
	t_color	color;

	if (data->ray.side == 0 && data->player.position.x - data->ray.map.x < 0)
		color = set_color("BLUE");
	else if (data->ray.side == 0 && data->player.position.x - data->ray.map.x > 0)
		color = set_color("RED");
	else if (data->ray.side == 1 && data->player.position.y - data->ray.map.y < 0)
		color = set_color("GRAY");
	else
		color = set_color("GREEN");
	return (color);
}

t_color		set_color(char *str)
{
	t_color	color;

	if (ft_strcmp("RED", str) == 0)
	{
		color.b = 0;
		color.g = 0;
		color.r = 255;
		color.a = 0;
	}
	if (ft_strcmp("BLUE", str) == 0)
	{
		color.b = 255;
		color.g = 0;
		color.r = 0;
		color.a = 0;
	}
	if (ft_strcmp("GREEN", str) == 0)
	{
		color.b = 86;
		color.g = 155;
		color.r = 35;
		color.a = 0;
	}
	if (ft_strcmp("GRAY", str) == 0)
	{
		color.b = 184;
		color.g = 183;
		color.r = 170;
		color.a = 0;
	}
	return (color);
}

void		new_frame(unsigned char *pixels, int size)
{
	int 	i;

	i = 0;
	while (i < size / 2)
	{
		pixels[i] = 255;
		pixels[i + 1] = 204;
		pixels[i + 2] = 153;
		pixels[i + 3] = 0;
		i += 4;
	}
	while (i < size)
	{
		pixels[i] = 205;
		pixels[i + 1] = 229;
		pixels[i + 2] = 252;
		pixels[i + 3] = 0;
		i += 4;
	}
}

void 		put_pixel(unsigned char *pixel, t_color color)
{
	pixel[0] = color.b;
	pixel[1] = color.g;
	pixel[2] = color.r;
	pixel[3] = color.a;
}

void		put_column(t_variables **data, int x, double size, t_color color)
{
	double count;
	int save;

	count = 0;
	save = x;
	x = save + ((MAX_X * 4) * (MAX_Y / 2));
	while (count < size / 2)
	{
		put_pixel(&(*data)->mlx.pixel[x], color);
		x = x + 5120;
		count++;
	}
	count = 0;
	x = save + ((MAX_X * 4) * (MAX_Y / 2));
	while (count < size / 2)
	{
		put_pixel(&(*data)->mlx.pixel[x], color);
		x = x - 5120;
		count++;
	}
}
