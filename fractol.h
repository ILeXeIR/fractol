/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 18:34:59 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/17 17:26:27 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

// # define WIDTH 3840
// # define HEIGHT 1983
# define WIDTH 1200
# define HEIGHT 800
# define MAX_ITERATIONS 50

typedef struct s_grid
{
	double	x_min;
	double	x_max;
	double	y_min;
	double	y_max;
	double	x_step;
	double	y_step;
	double	x0;
	double	y0;
}	t_grid;

typedef struct s_fractal
{
	t_grid		*grid;
	mlx_image_t	*image;
}	t_fractal;

#endif