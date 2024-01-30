/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:49:36 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 19:25:06 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int32_t	get_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	min(int32_t x, int32_t y)
{
	if (x < y)
		return (x);
	return (y);
}

int32_t	max(int32_t x, int32_t y)
{
	if (x < y)
		return (y);
	return (x);
}

double	get_double(char *s)
{
	double	num;
	double	divider;
	int		sign;

	num = 0;
	sign = 1;
	divider = 1;
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	while ('0' <= *s && *s <= '9')
		num = num * 10 + (*s++ - '0');
	if (*s == '.')
		s++;
	while ('0' <= *s && *s <= '9')
	{
		divider /= 10;
		num += divider * (*s++ - '0');
	}
	return (num * sign);
}

double	get_escape_radius(double cx, double cy)
{
	double	discriminant;
	double	radius;

	discriminant = 1 + 4 * sqrt(cx * cx + cy * cy);
	radius = (1 + sqrt(discriminant)) / 2;
	return (radius);
}
