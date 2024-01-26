/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/26 20:44:06 by alpetukh      ########   odam.nl         */
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

int	count_iterations_m(double x0, double y0, uint32_t max_iter)
{
	long double	x;
	long double	y;
	long double	xtemp;
	uint32_t	iteration;

	x = 0;
	y = 0;
	iteration = 0;
	while (x * x + y * y <= 4 && iteration < max_iter)
	{
		xtemp = x * x - y * y + x0;
		y = 2 * x * y + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	count_iterations_j(double x, double y, double cx, double cy, uint32_t max_iter)
{
	long double	xtemp;
	uint32_t	iteration;

	iteration = 0;
	while (x * x + y * y <= 4 && iteration < max_iter)
	{
		xtemp = x * x - y * y + cx;
		y = 2 * x * y + cy;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

int	get_iterations(t_fractal *f)
{
	t_grid	*grid;

	grid = f->grid;
	if (f->set == MANDELBROT)
		return (count_iterations_m(grid->x0, grid->y0, f->max_iter));
	else if (f->set == JULIA)
		return (count_iterations_j(grid->x0, grid->y0, grid->cx, grid->cy, f->max_iter));
	return (0);
}

void	draw_fractal(void *param)
{
	t_fractal	*f;
	uint32_t	x;
	uint32_t	y;
	uint32_t	iteration;
	uint32_t	color;

	f = param;
	y = 0;
	f->grid->y0 = f->grid->y_min;
	while (y < f->image->height)
	{
		x = 0;
		f->grid->x0 = f->grid->x_min;
		while (x < f->image->width)
		{
			iteration = get_iterations(f);
			color = choose_color(iteration, f->color_schema, f->max_iter);
			mlx_put_pixel(f->image, x, y, color);
			x++;
			f->grid->x0 += f->grid->step;
		}
		y++;
		f->grid->y0 += f->grid->step;
	}
}

void	grid_init_m(t_grid *grid, mlx_image_t *image)
{
	grid->y_min = -1.25;
	grid->y_max = 1.25;
	grid->x_min = grid->y_min * image->width / image->height - 1;
	grid->x_max = grid->y_max * image->width / image->height - 1;
	grid->step = (grid->y_max - grid->y_min) / image->height;
}

void	grid_init_j(t_grid *grid, mlx_image_t *image)
{
	double	r;

	r = 2;
	grid->y_min = -r;
	grid->y_max = r;
	grid->x_min = grid->y_min * image->width / image->height;
	grid->x_max = grid->y_max * image->width / image->height;
	grid->step = (grid->y_max - grid->y_min) / image->height;
}

void	grid_init(t_fractal *fractal)
{
	if (fractal->set == MANDELBROT)
		grid_init_m(fractal->grid, fractal->image);
	else if (fractal->set == JULIA)
		grid_init_j(fractal->grid, fractal->image);
}

void	fract_ol(t_set name, double cx, double cy, uint32_t max_iter)
{
	mlx_t		*mlx;
	t_grid		grid;
	t_fractal	fractal;

	mlx = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
	if (mlx == NULL)
		clean_and_exit(NULL, 3);
	fractal.image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (fractal.image == NULL)
		clean_and_exit(mlx, 4);
	if (mlx_image_to_window(mlx, fractal.image, 0, 0) == -1)
		clean_and_exit(mlx, 5);
	grid.cx = cx;
	grid.cy = cy;
	fractal.mlx = mlx;
	fractal.grid = &grid;
	fractal.color_schema = 1;
	fractal.set = name;
	fractal.max_iter = max_iter;
	grid_init(&fractal);
	mlx_scroll_hook(mlx, &handle_zoom, &fractal);
	mlx_loop_hook(mlx, &handle_keys, &fractal);
	// mlx_loop_hook(mlx, &fill_image, fractal.image);
	mlx_loop_hook(mlx, &draw_fractal, &fractal);
	mlx_loop(mlx);
	mlx_close_window(mlx);
	mlx_terminate(mlx);
}

int	parse_iterations(char *s)
{
	int	num;

	num = ft_atoi(s);
	if (num < 1 || num > 1000)
		clean_and_exit(NULL, 2);
	return (num);
}

int	main(int argc, char *argv[])
{
	double	cx;
	double	cy;
	int		max_iter;

	max_iter = 100;
	cx = -0.8;
	cy = 0.156;
	if (argc > 1 && argc < 4 && ft_strncmp(argv[1], "m", 2) == 0)
	{
		if (argc == 3)
			max_iter = parse_iterations(argv[2]);
		fract_ol(MANDELBROT, 0, 0, max_iter + 1);
	}
	else if (argc > 1 && argc < 6 && ft_strncmp(argv[1], "j", 2) == 0)
	{
		if (argc == 3 || argc == 5)
			max_iter = parse_iterations(argv[argc - 1]);
		if (argc > 3)
		{
			cx = get_double(argv[2]);
			cy = get_double(argv[3]);
		}
		fract_ol(JULIA, cx, cy, max_iter + 1);
	}
	else
		clean_and_exit(NULL, 1);
	return (0);
}
