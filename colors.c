/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   colors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:54:07 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/18 18:27:52 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int32_t	get_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	choose_color(uint32_t iteration)
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
}

// int32_t	choose_color(uint32_t iteration)
// {
// 	int32_t	r;
// 	int32_t	g;
// 	int32_t	b;
// 	int32_t	a;

// 	r = 0;
// 	g = 0;
// 	b = 0;
// 	a = 255;
// 	if (iteration == MAX_ITERATIONS)
// 		return (get_color(r, g, b, a));
// 	b = 255;
// 	if (iteration > MAX_ITERATIONS / 2)
// 		r = iteration * 255 / MAX_ITERATIONS;
// 	if (iteration > MAX_ITERATIONS * 4 / 5)
// 	{
// 		b = 0;
// 		g = iteration * 255 / MAX_ITERATIONS;
// 	}
// 	a = iteration * 155 / MAX_ITERATIONS + 100;
// 	return (get_color(r, g, b, a));
// }
