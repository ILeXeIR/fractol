/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hooks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/18 17:49:31 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/18 19:47:25 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
	{
		printf("X: %Le - %Le,\tY: %Le - %Le\n", grid->x_min, grid->x_max, grid->y_min, grid->y_max);
		// printf("%f\n", mlx->delta_time);
	}
}

static void	zoom_fractal(t_grid *grid, mlx_image_t *image, mlx_t *mlx, int sign)
{
	long double	x_change;
	long double	y_change;
	int32_t		x_pos;
	int32_t		y_pos;
	long double	x0_pos_old;
	long double	y0_pos_old;

	mlx_get_mouse_pos(mlx, &x_pos, &y_pos);
	x0_pos_old = (grid->x_max - grid->x_min) * ((long double)x_pos / image->width - 0.5);
	y0_pos_old = (grid->y_max - grid->y_min) * ((long double)y_pos / image->height - 0.5);
	x_change = (grid->x_max - grid->x_min) * 0.05;
	grid->x_min += x_change * sign;
	grid->x_max -= x_change * sign;
	y_change = (grid->y_max - grid->y_min) * 0.05;
	grid->y_min += y_change * sign;
	grid->y_max -= y_change * sign;
	grid->x_step = (grid->x_max - grid->x_min) / image->width;
	grid->y_step = (grid->y_max - grid->y_min) / image->height;
	// x0_pos_new = (grid->x_max - grid->x_min) * x_pos / image->width;
	// y0_pos_new = (grid->y_max - grid->y_min) * y_pos / image->height;
	grid->x_min += x0_pos_old * 0.1 * sign;
	grid->x_max += x0_pos_old * 0.1 * sign;
	grid->y_min += y0_pos_old * 0.1 * sign;
	grid->y_max += y0_pos_old * 0.1 * sign;
}

void	handle_zoom(double xdelta, double ydelta, void *param)
{
	t_fractal	*fractal;

	fractal = param;
	// printf("POS: %d, %d\n", x_pos, y_pos);
	if (ydelta > 0)
		zoom_fractal(fractal->grid, fractal->image, fractal->mlx, 1);
	else if (ydelta < 0)
		zoom_fractal(fractal->grid, fractal->image, fractal->mlx, -1);
	(void)xdelta;
}

void	handle_cursor(double xpos, double ypos, void *param)
{
	t_fractal		*fractal;
	t_grid			*grid;
	int				sign;
	long double		delta;

	fractal = param;
	grid = fractal->grid;
	sign = 0;
	if (xpos < fractal->image->width / 3)
		sign = -1;
	else if (xpos > fractal->image->width * 2 / 3)
		sign = 1;
	delta = (grid->x_max - grid->x_min) * sign * 0.003;
	grid->x_min += delta;
	grid->x_max += delta;
	sign = 0;
	if (ypos < fractal->image->height / 3)
		sign = -1;
	else if (ypos > fractal->image->height * 2 / 3)
		sign = 1;
	delta = (grid->y_max - grid->y_min) * sign * 0.003;
	grid->y_min += delta;
	grid->y_max += delta;
}
