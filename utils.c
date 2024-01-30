/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/30 19:16:11 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 19:33:25 by alpetukh      ########   odam.nl         */
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

int	parse_iterations(char *s)
{
	int	num;

	num = ft_atoi(s);
	if (num < 1 || num > 1000)
		clean_and_exit(NULL, 2);
	return (num);
}

t_set	get_fractal_type(char *s)
{
	if (ft_strncmp(s, "m", 2) == 0)
		return (MANDELBROT);
	else if (ft_strncmp(s, "j", 2) == 0)
		return (JULIA);
	else if (ft_strncmp(s, "b", 2) == 0)
		return (BURNING_SHIP);
	clean_and_exit(NULL, 1);
	exit(1);
}

void	move_image(long double *i_min, long double *i_max, int sign)
{
	long double	i_change;

	i_change = (*i_max - *i_min) * 0.1L * (long double)sign;
	*i_min += i_change;
	*i_max += i_change;
}

int32_t	choose_color(uint32_t iter, int32_t palette, uint32_t max_iter)
{
	if (palette == 1)
		return (palette_1(iter, max_iter));
	else if (palette == 2)
		return (palette_2(iter, max_iter));
	else if (palette == 3)
		return (palette_3(iter, max_iter));
	return (0);
}
