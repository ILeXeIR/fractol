/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:49:31 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 19:30:11 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	change_palette(mlx_t *mlx, t_fractal *fractal)
{
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		fractal->palette = 1;
	else if (mlx_is_key_down(mlx, MLX_KEY_2))
		fractal->palette = 2;
	else if (mlx_is_key_down(mlx, MLX_KEY_3))
		fractal->palette = 3;
}

void	handle_keys(void *param)
{
	t_fractal	*fractal;
	mlx_t		*mlx;
	t_grid		*grid;

	fractal = param;
	mlx = fractal->mlx;
	grid = fractal->grid;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) \
			&& !mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		move_image(&grid->x_min, &grid->x_max, -1);
	else if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) \
			&& !mlx_is_key_down(mlx, MLX_KEY_LEFT))
		move_image(&grid->x_min, &grid->x_max, 1);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) \
			&& !mlx_is_key_down(mlx, MLX_KEY_DOWN))
		move_image(&grid->y_min, &grid->y_max, -1);
	else if (mlx_is_key_down(mlx, MLX_KEY_DOWN) \
			&& !mlx_is_key_down(mlx, MLX_KEY_UP))
		move_image(&grid->y_min, &grid->y_max, 1);
	change_palette(mlx, fractal);
}

static void	get_cursor_coordinates(long double *x0_pos, long double *y0_pos, \
	t_fractal *fractal)
{
	int32_t		x_pos;
	int32_t		y_pos;
	long double	x_size;
	long double	y_size;

	mlx_get_mouse_pos(fractal->mlx, &x_pos, &y_pos);
	x_size = fractal->grid->x_max - fractal->grid->x_min;
	y_size = fractal->grid->y_max - fractal->grid->y_min;
	*x0_pos = x_size * ((long double)x_pos / fractal->image->width - 0.5);
	*y0_pos = y_size * ((long double)y_pos / fractal->image->height - 0.5);
}

static void	zoom_fractal(t_grid *grid, t_fractal *fractal, int sign)
{
	long double	x_change;
	long double	y_change;
	long double	x0_pos;
	long double	y0_pos;
	mlx_image_t	*image;

	get_cursor_coordinates(&x0_pos, &y0_pos, fractal);
	image = fractal->image;
	x_change = (grid->x_max - grid->x_min) * 0.05;
	grid->x_min += x_change * sign;
	grid->x_max -= x_change * sign;
	y_change = (grid->y_max - grid->y_min) * 0.05;
	grid->y_min += y_change * sign;
	grid->y_max -= y_change * sign;
	grid->step *= (1 - 0.1 * sign);
	grid->x_min += x0_pos * 0.1 * sign;
	grid->x_max += x0_pos * 0.1 * sign;
	grid->y_min += y0_pos * 0.1 * sign;
	grid->y_max += y0_pos * 0.1 * sign;
}

void	handle_zoom(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
		zoom_fractal(fractal->grid, fractal, 1);
	else if (ydelta < 0)
		zoom_fractal(fractal->grid, fractal, -1);
	(void)xdelta;
}
