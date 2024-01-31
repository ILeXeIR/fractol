/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:54:07 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/31 19:35:41 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int32_t	palette_1(uint32_t iteration, uint32_t max_iter)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = 0;
	g = 0;
	b = 0;
	a = 255;
	if (iteration == max_iter)
		return (get_color(r, g, b, a));
	if (iteration < 10)
		a = iteration * 155 / 10 + 100;
	if (iteration > 70)
		b = max(100 - iteration, 0) * 255 / 30;
	else
		b = 255;
	if (iteration > 5)
		r = min(iteration - 5, 35) * 255 / 35;
	if (iteration > 40)
		g = min(iteration - 40, 30) * 255 / 30;
	return (get_color(r, g, b, a));
}

int32_t	palette_2(uint32_t iteration, uint32_t max_iter)
{
	if (iteration == max_iter)
		return (0xFFFFFFFF);
	return (0xFFA00000 + iteration * 255 / max_iter);
}

int32_t	palette_3(uint32_t iteration, uint32_t max_iter)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
	int32_t	color;

	color = palette_1(iteration, max_iter);
	r = (color >> 24);
	b = 255 - ((color >> 16) & 0xFF);
	g = (color >> 8) & 0xFF;
	a = color & 0xFF;
	return (get_color(r, g, b, a));
}

int32_t	palette_4(uint32_t iteration)
{
	const int32_t	colors[] = {0xFF0000FF, 0xFFA000FF, 0xFFFF00FF,
		0x00FF00FF, 0x00FFFFFF, 0x0000FFFF, 0xBB00FFFF, 0xFF00A0FF};

	return (colors[iteration % 8]);
}

int32_t	palette_5(uint32_t iteration, uint32_t max_iter)
{
	int32_t			r;
	int32_t			g;
	int32_t			b;

	if (iteration == max_iter)
		return (0x734000BB);
	if (iteration % 30 < 10)
	{
		r = 0x26 + (iteration % 10) * (0xFF - 0x26) / 10;
		g = 0x99 + (iteration % 10) * (0xFF - 0x99) / 10;
		b = 0x42 + (iteration % 10) * (0xFF - 0x42) / 10;
	}
	else if (iteration % 30 < 20)
	{
		r = 0xFF + (int32_t)(iteration % 10) * (0x73 - 0xFF) / 10;
		g = 0xFF + (int32_t)(iteration % 10) * (0x40 - 0xFF) / 10;
		b = 0xFF + (int32_t)(iteration % 10) * (0x00 - 0xFF) / 10;
	}
	else
	{
		r = 0x73 + (int32_t)(iteration % 10) * (0x26 - 0x73) / 10;
		g = 0x40 + (int32_t)(iteration % 10) * (0x99 - 0x40) / 10;
		b = 0x00 + (int32_t)(iteration % 10) * (0x42 - 0x00) / 10;
	}
	return (get_color(r, g, b, 0xFF));
}
