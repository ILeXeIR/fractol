/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/15 18:34:59 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/18 18:54:37 by alpetukh      ########   odam.nl         */
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
# define MAX_ITERATIONS 100

typedef struct s_grid
{
	long double	x_min;
	long double	x_max;
	long double	y_min;
	long double	y_max;
	long double	x_step;
	long double	y_step;
	long double	x0;
	long double	y0;
}	t_grid;

typedef struct s_fractal
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_grid		*grid;
}	t_fractal;

void	handle_keys(void *param);
void	handle_zoom(double xdelta, double ydelta, void *param);
void	handle_cursor(double xpos, double ypos, void *param);

void	clean_and_exit(mlx_t *mlx, int code);
int32_t	min(int32_t x, int32_t y);
int32_t	max(int32_t x, int32_t y);

int32_t	choose_color(uint32_t iteration);

#endif