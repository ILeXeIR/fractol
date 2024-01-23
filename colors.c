/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:54:07 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/23 19:57:05 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int32_t	get_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static int32_t	color_schema_1(uint32_t iteration)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = 0;
	g = 0;
	b = 0;
	a = 255;
	if (iteration == MAX_ITERATIONS)
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

static int32_t	color_schema_2(uint32_t iteration)
{
	if (iteration == MAX_ITERATIONS)
		return (0xFF);
	return (0xFFFFFF00 + iteration * 255 / MAX_ITERATIONS);
}

static int32_t	color_schema_3(uint32_t iteration)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;
	int32_t	color;

	color = color_schema_1(iteration);
	r = (color >> 24);
	b = 255 - ((color >> 16) & 0xFF);
	g = (color >> 8) & 0xFF;
	a = color & 0xFF;
	return (get_color(r, g, b, a));
}

int32_t	choose_color(uint32_t iteration, int32_t color_schema)
{
	if (color_schema == 1)
		return (color_schema_1(iteration));
	else if (color_schema == 2)
		return (color_schema_2(iteration));
	else if (color_schema == 3)
		return (color_schema_3(iteration));
	return (0);
}
