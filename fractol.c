/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/16 19:55:58 by alpetukh      ########   odam.nl         */
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

void	draw_fractal(void	*param)
{
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;
	uint32_t	iteration;
	uint32_t	color;
	double		x_min = -2;
	double		x_max = 0.47;
	double		y_min = -1.12;
	double		y_max = 1.12;
	double		x_step;
	double		y_step;
	double		x0;
	double		y0;

	image = param;
	x_step = (x_max - x_min) / image->width;
	y_step = (y_max - y_min) / image->height;
	y = 0;
	y0 = y_min;
	while (y < image->height)
	{
		x = 0;
		x0 = x_min;
		while (x < image->width)
		{
			iteration = count_iterations(x0, y0);
			color = choose_color(iteration);
			mlx_put_pixel(image, x, y, color);
			x++;
			x0 += x_step;
		}
		y++;
		y0 += y_step;
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

int	main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	if (mlx == NULL)
		clean_and_exit(mlx, 1);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (image == NULL)
		clean_and_exit(mlx, 2);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
		clean_and_exit(mlx, 3);
	mlx_loop_hook(mlx, &handle_keys, mlx);
	// mlx_loop_hook(mlx, &fill_image, image);
	mlx_loop_hook(mlx, &draw_fractal, image);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
