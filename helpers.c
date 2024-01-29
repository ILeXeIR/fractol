/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:49:36 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/29 16:48:26 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_and_exit(mlx_t *mlx, int code)
{
	const char	*args_error_msg = "ERROR with arguments.\n\nUsage:\n"
		"fractal [SET] [CX] [CY] [MAX_ITER]\n\n"
		"SET\n\tValue: 'm' or 'j'\n\tChoose Mandelbrot or Julia set\n\n"
		"CX, CY\n\tValue: double\n\t"
		"(Optional) Parameters of the fractal Julia. "
		"You can use both or none of them only.\n\n"
		"MAX_ITER\n\tValue: integer from 1 to 1000\n\t(Optional) "
		"Maximum iterations to calculate a color of each pixel.";

	if (code < 3)
		ft_printf("%s\n", args_error_msg);
	else
		printf("ERROR\n");
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
