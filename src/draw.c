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

void 		put_pixel(unsigned char *pixel, t_color color)
{
	pixel[0] = color.B;
	pixel[1] = color.G;
	pixel[2] = color.R;
	pixel[3] = color.A;
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
