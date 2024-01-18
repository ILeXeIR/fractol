/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/18 19:17:14 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	fill_image(void	*param)
// {
// 	mlx_image_t	*image;
// 	uint32_t	x;
// 	uint32_t	y;
// 	uint32_t	color;

// 	image = param;
// 	y = 0;
// 	while (y < image->height)
// 	{
// 		x = 0;
// 		while (x < image->width)
// 		{
// 			if (x < 100)
// 				color = get_color(0, 0, 0, 255);
// 			else
// 				color = get_color(100, 0, 100, 100);
// 			mlx_put_pixel(image, x, y, color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

int	count_iterations(double x0, double y0)
{
	long double		x;
	long double		y;
	long double		xtemp;
	uint32_t		iteration;

	x = 0;
	y = 0;
	iteration = 0;
	while (x * x + y * y <= 4 && iteration < MAX_ITERATIONS)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

void	draw_fractal(void *param)
{
	t_fractal	*fractal;
	uint32_t	x;
	uint32_t	y;
	uint32_t	iteration;
	uint32_t	color;

	fractal = param;
	y = 0;
	fractal->grid->y0 = fractal->grid->y_min;
	while (y < fractal->image->height)
	{
		x = 0;
		fractal->grid->x0 = fractal->grid->x_min;
		while (x < fractal->image->width)
		{
			iteration = count_iterations(fractal->grid->x0, fractal->grid->y0);
			color = choose_color(iteration);
			mlx_put_pixel(fractal->image, x, y, color);
			x++;
			fractal->grid->x0 += fractal->grid->x_step;
		}
		y++;
		fractal->grid->y0 += fractal->grid->y_step;
	}
}

void	grid_init(t_grid *grid, mlx_image_t *image)
{
	grid->y_min = -1.25;
	grid->y_max = 1.25;
	grid->x_min = grid->y_min * image->width / image->height - 1;
	grid->x_max = grid->y_max * image->width / image->height - 1;
	grid->x_step = (grid->x_max - grid->x_min) / image->width;
	grid->y_step = (grid->y_max - grid->y_min) / image->height;
}

int	main(void)
{
	mlx_t		*mlx;
	t_grid		grid;
	t_fractal	fractal;

	// mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	if (mlx == NULL)
		clean_and_exit(mlx, 1);
	fractal.image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (fractal.image == NULL)
		clean_and_exit(mlx, 2);
	if (mlx_image_to_window(mlx, fractal.image, 0, 0) == -1)
		clean_and_exit(mlx, 3);
	fractal.mlx = mlx;
	fractal.grid = &grid;
	grid_init(fractal.grid, fractal.image);
	mlx_loop_hook(mlx, &handle_keys, &fractal);
	mlx_scroll_hook(mlx, &handle_zoom, &fractal);
	// mlx_cursor_hook(mlx, &handle_cursor, &fractal);
	// mlx_loop_hook(mlx, &fill_image, image);
	mlx_loop_hook(mlx, &draw_fractal, &fractal);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
