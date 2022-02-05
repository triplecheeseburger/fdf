/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:41 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 00:35:44 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	project_isometric(int *x, int *y, int *z)
{
	int prev_x;
	int prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(0.523599));
	*y = ((prev_x + prev_y) * sin(0.523599) - *z);
}

void	set_start(t_data *data, int x, int y)
{
	data->x_start = x * ZOOM;
	data->y_start = y * ZOOM;
	data->z_start = data->map[y][x] * ZOOM;
	data->color_start = data->color_map[y][x];
	data->x_start -= (data->width * ZOOM) / 2;
	data->y_start -= (data->height * ZOOM) / 2;
	project_isometric(&data->x_start, &data->y_start, &data->z_start);
	data->x_start += WIDTH / 2;
	data->y_start += (HEIGHT + data->height * ZOOM) / 2;
	data->x_cur = data->x_start;
	data->y_cur = data->y_start;
	data->z_cur = data->z_start;
}

void	set_end(t_data *data, int x, int y)
{
	data->x_end = x * ZOOM;
	data->y_end = y * ZOOM;
	data->z_end = data->map[y][x] * ZOOM;
	data->color_end = data->color_map[y][x];
	data->x_end -= (data->width * ZOOM) / 2;
	data->y_end -= (data->height * ZOOM) / 2;
	project_isometric(&data->x_end, &data->y_end, &data->z_end);
	data->x_end += WIDTH / 2;
	data->y_end += (HEIGHT + data->height * ZOOM) / 2;
}

// data->addr[x * data->bpp / 8 + y * data->size_line] = data->color?;

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	draw_line(t_data *data)
{
	data->addr[data->x_start + data->y_start * data->size_line / 4] = data->color_start;
}

void	plot_dot(t_data *data, int x, int y, int color)
{
	data->addr[x + y * data->size_line / 4] = color;
}

double f_part(double x)
{
	return (x - floor(x));
}

double rf_part(double x)
{
	return (1 - f_part(x));
}

void	xiaoline(t_data *data)
{

}

void	draw_image(t_data *data)
{
	int		x;
	int		y;

	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (x < data->width - 1)
			{
				set_start(data, x, y);
				set_end(data, x + 1, y);
				draw_line(data);
			}
			if (y < data->height - 1)
			{
				set_start(data, x, y);
				set_end(data, x, y + 1);
				draw_line(data);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}

int key_press(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int red_button(int exitcode)
{
	exit(exitcode);
}

void	init_data(t_data *data)
{
	data->width = 0;
	data->height = 0;
}

int	main(int ac, char **av)
{
	t_data data;

	if (ac != 2)
		return (0);
	init_data(&data);
	fill_map(av[1], &data);
	print_map(&data);
	print_color_map(&data);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FDF");
	mlx_hook(data.window, 2, 0, key_press, &data);
	mlx_hook(data.window, 17, 0, red_button, 0);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = (int *)mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
//	for (int i = 0; i < 1; i++)
//	{
//		for (int j = 0; j < data.size_line / 8; j++)
//			data.addr[(i + 20) * data.size_line + j] = 0xFFFFFF;
//	}
//	mlx_put_image_to_window(data.mlx, data.window, data.img, 0, 0);
	draw_image(&data);
	mlx_loop(data.mlx);
}
