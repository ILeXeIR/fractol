/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/30 18:58:05 by alpetukh      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

uint32_t	count_iterations_m(double x0, double y0, uint32_t max_iter)
{
	long double	x;
	long double	y;
	long double	xtemp;
	uint32_t	iteration;

	x = x0;
	y = y0;
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

uint32_t	count_iterations_b(double x0, double y0, uint32_t max_iter)
{
	long double	x;
	long double	y;
	long double	xtemp;
	uint32_t	iteration;

	x = x0;
	y = y0;
	iteration = 0;
	while (x * x + y * y <= 4 && iteration < max_iter)
	{
		xtemp = x * x - y * y + x0;
		y = fabsl(2 * x * y) + y0;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

uint32_t	count_iterations_j(double x, double y, t_grid *grid)
{
	long double	xtemp;
	uint32_t	iteration;

	iteration = 0;
	while (x * x + y * y <= grid->escape && iteration < grid->max_iter)
	{
		xtemp = x * x - y * y + grid->cx;
		y = 2 * x * y + grid->cy;
		x = xtemp;
		iteration++;
	}
	return (iteration);
}

uint32_t	get_iterations(t_fractal *f)
{
	t_grid	*grid;

	grid = f->grid;
	if (f->set == MANDELBROT)
		return (count_iterations_m(grid->x0, grid->y0, grid->max_iter));
	else if (f->set == BURNING_SHIP)
		return (count_iterations_b(grid->x0, grid->y0, grid->max_iter));
	else if (f->set == JULIA)
		return (count_iterations_j(grid->x0, grid->y0, grid));
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
			color = choose_color(iteration, f->palette, f->grid->max_iter);
			mlx_put_pixel(f->image, x, y, color);
			x++;
			f->grid->x0 += f->grid->step;
		}
		y++;
		f->grid->y0 += f->grid->step;
	}
}

double	get_escape_radius(double cx, double cy)
{
	double	discriminant;
	double	radius;

	discriminant = 1 + 4 * sqrt(cx * cx + cy * cy);
	radius = (1 + sqrt(discriminant)) / 2;
	return (radius);
}

void	grid_init(t_fractal *fractal, double cx, double cy, uint32_t max_iter)
{
	t_grid		*grid;
	mlx_image_t	*image;
	double		r;

	grid = fractal->grid;
	image = fractal->image;
	if (fractal->set == JULIA)
		r = get_escape_radius(cx, cy);
	else
		r = 2.0;
	grid->cx = cx;
	grid->cy = cy;
	grid->y_min = -r;
	grid->y_max = r;
	grid->x_min = grid->y_min * image->width / image->height;
	grid->x_max = grid->y_max * image->width / image->height;
	grid->step = (grid->y_max - grid->y_min) / image->height;
	grid->escape = r * r;
	grid->max_iter = max_iter;
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
	fractal.mlx = mlx;
	fractal.grid = &grid;
	fractal.palette = 1;
	fractal.set = name;
	grid_init(&fractal, cx, cy, max_iter);
	mlx_scroll_hook(mlx, &handle_zoom, &fractal);
	mlx_loop_hook(mlx, &handle_keys, &fractal);
	mlx_loop_hook(mlx, &draw_fractal, &fractal);
	mlx_loop(mlx);
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

int	main(int argc, char *argv[])
{
	double	cx;
	double	cy;
	int		max_iter;
	t_set	set;

	max_iter = 100;
	cx = -0.8;
	cy = 0.156;
	if (argc < 2 || argc > 5)
		clean_and_exit(NULL, 1);
	set = get_fractal_type(argv[1]);
	if (argc == 3 || argc == 5)
		max_iter = parse_iterations(argv[argc - 1]);
	if (argc > 3)
	{
		if (set != JULIA)
			clean_and_exit(NULL, 1);
		cx = get_double(argv[2]);
		cy = get_double(argv[3]);
	}
	fract_ol(set, cx, cy, max_iter);
	return (0);
}
