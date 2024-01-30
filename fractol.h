/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 18:34:59 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 18:55:00 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/MLX42.h"

// # define WIDTH 3840
// # define HEIGHT 1983
# define WIDTH 1200
# define HEIGHT 800

typedef struct s_grid
{
	long double	x_min;
	long double	x_max;
	long double	y_min;
	long double	y_max;
	long double	step;
	long double	x0;
	long double	y0;
	double		cx;
	double		cy;
	double		escape;
	uint32_t	max_iter;
}	t_grid;

typedef enum e_set
{
	MANDELBROT = 1,
	JULIA = 2,
	BURNING_SHIP = 3
}	t_set;

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_grid		*grid;
	t_set		set;
	int32_t		palette;
}	t_fractal;

void	handle_keys(void *param);
void	handle_zoom(double xdelta, double ydelta, void *param);

void	clean_and_exit(mlx_t *mlx, int code);
void	move_image(long double *i_min, long double *i_max, int sign);
int32_t	min(int32_t x, int32_t y);
int32_t	max(int32_t x, int32_t y);
double	get_double(char *s);

int32_t	choose_color(uint32_t iteration, int32_t palette, uint32_t max_iter);

#endif