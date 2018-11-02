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

void		put_column(unsigned char *pixel, int x, double size, t_color color)
{
	double count;
	int save;

	count = 0;
	save = x;
	x = save + ((MAX_X * 4) * (MAX_Y / 2));
	while (count < size / 2)
	{
		put_pixel(&pixel[x], color);
		x = x + 5120;
		count++;
	}
	count = 0;
	x = save + ((MAX_X * 4) * (MAX_Y / 2));
	while (count < size / 2)
	{
		put_pixel(&pixel[x], color);
		x = x - 5120;
		count++;
	}
}
