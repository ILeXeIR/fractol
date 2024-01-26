/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:49:36 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/26 20:02:36 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_and_exit(mlx_t *mlx, int code)
{
	if (code > 3)
	{
		mlx_close_window(mlx);
		mlx_terminate(mlx);
	}
	exit (1);
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

void	move_image(long double *i_min, long double *i_max, int sign)
{
	long double	i_change;

	i_change = (*i_max - *i_min) * 0.1L * (long double)sign;
	*i_min += i_change;
	*i_max += i_change;
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
