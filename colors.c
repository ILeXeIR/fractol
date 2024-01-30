/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:54:07 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 18:54:02 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int32_t	get_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int32_t	palette_1(uint32_t iteration, uint32_t max_iter)
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
	return (get_color(255, 255, 255, 255));
}

static int32_t	palette_2(uint32_t iteration, uint32_t max_iter)
{
	if (iteration == max_iter)
		return (0xFF);
	return (0xFFFFFF00 + iteration * 255 / max_iter);
}

static int32_t	palette_3(uint32_t iteration, uint32_t max_iter)
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

int32_t	choose_color(uint32_t iteration, int32_t palette, uint32_t max_iter)
{
	if (palette == 1)
		return (palette_1(iteration, max_iter));
	else if (palette == 2)
		return (palette_2(iteration, max_iter));
	else if (palette == 3)
		return (palette_3(iteration, max_iter));
	return (0);
}
