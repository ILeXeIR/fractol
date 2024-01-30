/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculators.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 19:08:16 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 19:14:17 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static uint32_t	count_iterations_m(double x0, double y0, uint32_t max_iter)
{
	long double	x;
	long double	y;
	long double	xtemp;
	uint32_t	iteration;

	x = x0;
	y = y0;
	iteration = 0;
	while (x * x + y * y <= 4 && iteration < max_iter)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

static uint32_t	count_iterations_b(double x0, double y0, uint32_t max_iter)
{
	long double	x;
	long double	y;
	long double	xtemp;
	uint32_t	iteration;

	x = x0;
	y = y0;
	iteration = 0;
	while (x * x + y * y <= 4 && iteration < max_iter)
	{
		xtemp = x * x - y * y + x0;
		y = fabsl(2 * x * y) + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

static uint32_t	count_iterations_j(double x, double y, t_grid *grid)
{
	long double	xtemp;
	uint32_t	iteration;

	iteration = 0;
	while (x * x + y * y <= grid->escape && iteration < grid->max_iter)
	{
		xtemp = x * x - y * y + grid->cx;
		y = 2 * x * y + grid->cy;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

uint32_t	get_iterations(t_fractal *f)
{
	t_grid	*grid;

	grid = f->grid;
	if (f->set == MANDELBROT)
		return (count_iterations_m(grid->x0, grid->y0, grid->max_iter));
	else if (f->set == BURNING_SHIP)
		return (count_iterations_b(grid->x0, grid->y0, grid->max_iter));
	else if (f->set == JULIA)
		return (count_iterations_j(grid->x0, grid->y0, grid));
	return (0);
}
