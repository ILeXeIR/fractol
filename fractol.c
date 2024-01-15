/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fractol.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: alpetukh <alpetukh@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/11 20:38:01 by alpetukh      #+#    #+#                 */
/*   Updated: 2024/01/15 20:40:30 by alpetukh      ########   odam.nl         */
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
				color = get_color(0, 255, 0, 255);
			else
				color = get_color(100, 0, 100, 100);
			mlx_put_pixel(image, x, y, color);
			x++;
		}
		y++;
	}
}

void	handle_keys(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		ft_printf("W: %d, H: %d\n", mlx->width, mlx->height);
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
	mlx_loop_hook(mlx, &fill_image, image);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
