/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/17 19:54:39 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	clean_and_exit(mlx_t *mlx, int code)
{
	if (code > 1)
		mlx_close_window(mlx);
	mlx_terminate(mlx);
	exit (1);
}

int32_t	get_color(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	choose_color(uint32_t iteration)
{
	int32_t	r;
	int32_t	g;
	int32_t	b;
	int32_t	a;

	r = 0;
	g = 0;
	b = 0;
	a = 255;
	if (iteration == MAX_ITERATIONS)
		return (get_color(r, g, b, a));
	b = 255;
	if (iteration > MAX_ITERATIONS / 2)
		r = iteration * 255 / MAX_ITERATIONS;
	if (iteration > MAX_ITERATIONS * 4 / 5)
	{
		b = 0;
		g = iteration * 255 / MAX_ITERATIONS;
	}
	a = iteration * 155 / MAX_ITERATIONS + 100;
	return (get_color(r, g, b, a));
}

void	fill_image(void	*param)
{
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;
	uint32_t	color;

	image = param;
	y = 0;
	while (y < image->height)
	{
		x = 0;
		while (x < image->width)
		{
			if (x < 100)
				color = get_color(0, 0, 0, 255);
			else
				color = get_color(100, 0, 100, 100);
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

int	count_iterations(double x0, double y0)
{
	double		x;
	double		y;
	double		xtemp;
	uint32_t	iteration;

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

void	handle_keys(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
	{
		ft_printf("W: %d, H: %d\n", mlx->width, mlx->height);
		printf("%f\n", mlx->delta_time);
	}
}

void	zoom_fractal(t_grid *grid, mlx_image_t *image, int sign)
{
	double	x_change;
	double	y_change;

	x_change = (grid->x_max - grid->x_min) * 0.05;
	grid->x_min += x_change * sign;
	grid->x_max -= x_change * sign;
	y_change = (grid->y_max - grid->y_min) * 0.05;
	grid->y_min += y_change * sign;
	grid->y_max -= y_change * sign;
	grid->x_step = (grid->x_max - grid->x_min) / image->width;
	grid->y_step = (grid->y_max - grid->y_min) / image->height;
}

void	handle_zoom(double xdelta, double ydelta, void* param)
{
	t_fractal	*fractal;

	fractal = param;
	if (ydelta > 0)
		zoom_fractal(fractal->grid, fractal->image, 1);
	else if (ydelta < 0)
		zoom_fractal(fractal->grid, fractal->image, -1);
	(void)xdelta;
}

void	grid_init(t_grid *grid, mlx_image_t *image)
{
	grid->x_min = -2;
	grid->x_max = 0.47;
	grid->y_min = -1.12;
	grid->y_max = 1.12;
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
	fractal.grid = &grid;
	grid_init(fractal.grid, fractal.image);
	if (fractal.image == NULL)
		clean_and_exit(mlx, 2);
	if (mlx_image_to_window(mlx, fractal.image, 0, 0) == -1)
		clean_and_exit(mlx, 3);
	mlx_loop_hook(mlx, &handle_keys, mlx);
	mlx_scroll_hook(mlx, &handle_zoom, &fractal);
	// mlx_loop_hook(mlx, &fill_image, image);
	mlx_loop_hook(mlx, &draw_fractal, &fractal);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
