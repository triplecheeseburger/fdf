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

void	project_isometric(double *x, double *y, double *z)
{
	double prev_x;
	double prev_y;

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
	data->x_start -= (data->width * ZOOM) / 2.0;
	data->y_start -= (data->height * ZOOM) / 2.0;
	project_isometric(&data->x_start, &data->y_start, &data->z_start);
	data->x_start += WIDTH / 2.0;
	data->y_start += (HEIGHT + data->height * ZOOM) / 2.0;
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
	data->x_end -= (data->width * ZOOM) / 2.0;
	data->y_end -= (data->height * ZOOM) / 2.0;
	project_isometric(&data->x_end, &data->y_end, &data->z_end);
	data->x_end += WIDTH / 2.0;
	data->y_end += (HEIGHT + data->height * ZOOM) / 2.0;
}

int ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	plot_dot(t_data *data, int x, int y, int color)
{
	if (0 < x + y * data->size_line / 4 && x + y * data->size_line / 4 < WIDTH * HEIGHT)
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

void	dd_swap(double *a, double *b, double *c, double *d)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
	temp = *c;
	*c = *d;
	*d = temp;
}

static double	ft_percent(int start, int end, int current)
{
	double	plac;
	double	dist;

	plac = current - start;
	dist = end - start;
	if (dist == 0)
		return (1.0);
	return ((plac / dist));
}

static int	ft_get_light(int start, int end, double percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

void	ft_get_color(t_data *data)
{
	int		r;
	int		g;
	int		b;
	double	percent;

//	if (data->color_cur == data->color_end)
//		return (data->color_cur);
//	if (x > y)
//	percent = ft_percent(data->x_start, data->x_end, data->x_cur);
//	else
		percent = ft_percent(data->y_start, data->y_end, data->y_cur);
	r = ft_get_light((data->color_start >> 16) & 0xFF, (data->color_end >> 16)
												& 0xFF, percent);
	g = ft_get_light((data->color_start >> 8) & 0xFF, (data->color_end >> 8)
											   & 0xFF, percent);
	b = ft_get_light(data->color_start & 0xFF, data->color_end & 0xFF, percent);
	data->color_cur = ((r << 16) | (g << 8) | b);
}

int	calc_color(t_data *data, double c)
{
	int color;
	int	r;
	int g;
	int b;

	r = (int)(c * (data->color_cur >> 16 & 0xFF));
	if (r > 255)
		r = 255;
	g = (int)(c * (data->color_cur >> 8 & 0xFF));
	if (g > 255)
		g = 255;
	b = (int)(c * (data->color_cur & 0xFF));
	if (b > 255)
		b = 255;
	color = r << 16;
	color += g << 8;
	color += b;
	return (color);
}

void	xiaoline(t_data *data, double dx, double dy)
{
	double	gradient;
	double	xend;
	double	yend;
	double	gap;
	double	inter;

	dx = data->x_end - data->x_start;
	dy = data->y_end - data->y_start;
	if (fabs(dx) > fabs(dy))
	{
		if (data->x_end < data->x_start)
			dd_swap(&data->x_start, &data->x_end, &data->y_start, &data->y_end);
		gradient = dy / dx;
		data->x_cur = (int)(data->x_start + 0.5);
		data->y_cur = data->y_start + gradient * (data->x_cur - data->x_start);
		gap = rf_part(data->x_start + 0.5);
		plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->y_cur) * gap));
		plot_dot(data, data->x_cur, data->y_cur + 1, calc_color(data, f_part(data->y_cur) * gap));
		inter = data->y_cur + gradient;
		xend = (int)(data->x_end + 0.5);
		yend = data->y_end + gradient * (xend - data->x_end);
		gap = f_part(data->x_end + 0.5);
//		plot_dot(data, xend, yend, calc_color(rf_part(yend) * gap));
//		plot_dot(data, xend, yend + 1, calc_color(f_part(yend) * gap));
		while (data->x_cur++ < xend)
		{
			ft_get_color(data);
			plot_dot(data, data->x_cur, inter, calc_color(data, rf_part(inter)));
			plot_dot(data, data->x_cur, inter + 1, calc_color(data, f_part(inter)));
			inter += gradient;
		}
	}
	else
	{
		if (data->y_end < data->y_start)
			dd_swap(&data->x_start, &data->x_end, &data->y_start, &data->y_end);
		gradient = dx / dy;
		data->y_cur = (int)(data->y_start + 0.5);
		data->x_cur = data->x_start + gradient * (data->y_cur - data->y_start);
		gap = rf_part(data->y_start + 0.5);
		plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->y_cur) * gap));
		plot_dot(data, data->x_cur + 1, data->y_cur, calc_color(data, f_part(data->y_cur) * gap));
		inter = data->x_cur + gradient;
		yend = (int)(data->y_end + 0.5);
		xend = data->y_end + gradient * (yend - data->x_end);
		gap = f_part(data->y_end + 0.5);
//		plot_dot(data, xend, yend, calc_color(rf_part(xend) * gap));
//		plot_dot(data, xend + 1, yend, calc_color(f_part(xend) * gap));
		while (data->y_cur++ < yend)
		{
			ft_get_color(data);
			plot_dot(data, inter, data->y_cur, calc_color(data, rf_part(inter)));
			plot_dot(data, inter + 1, data->y_cur, calc_color(data, f_part(inter)));
			inter += gradient;
		}
	}
}

//int	ft_comper(int a, int b)
//{
//	if (a < b)
//		return (1);
//	return (-1);
//}
//static double	ft_percent(int start, int end, int current)
//{
//	double	plac;
//	double	dist;
//
//	plac = current - start;
//	dist = end - start;
//	if (dist == 0)
//		return (1.0);
//	return ((plac / dist));
//}
//
//static int	ft_get_light(int start, int end, double percent)
//{
//	return ((int)((1 - percent) * start + percent * end));
//}
//
//unsigned int	ft_get_color(t_data *data, int x, int y)
//{
//	int		r;
//	int		g;
//	int		b;
//	double	percent;
//
//	if (data->color_cur == data->color_end)
//		return (data->color_cur);
//	if (x > y)
//		percent = ft_percent(data->x_start, data->x_end, data->x_cur);
//	else
//		percent = ft_percent(data->y_start, data->y_end, data->y_cur);
//	r = ft_get_light((data->color_start >> 16) & 0xFF, (data->color_end >> 16)
//												& 0xFF, percent);
//	g = ft_get_light((data->color_start >> 8) & 0xFF, (data->color_end >> 8)
//											   & 0xFF, percent);
//	b = ft_get_light(data->color_start & 0xFF, data->color_end & 0xFF, percent);
//	return (((r << 16) | (g << 8) | b));
//}
//
//static void	ft_draw_line(t_data *data, int sx, int sy)
//{
//	int	x;
//	int	y;
//	int	tmp[2];
//
//	x = ft_abs(data->x_end - data->x_start);
//	y = ft_abs(data->y_end - data->y_start);
//	sx = ft_comper(data->x_start, data->x_end);
//	sy = ft_comper(data->y_start, data->y_end);
//	tmp[0] = x - y;
//	while (0 < (int)(data->x_cur + data->y_cur * data->size_line / 4) && (int)(data->x_cur + data->y_cur * data->size_line / 4) < WIDTH * HEIGHT)
//	{
//		data->color_cur = ft_get_color(data, x, y);
//		data->addr[(int)(data->x_cur + data->y_cur * data->size_line / 4)] = data->color_cur;
//		tmp[1] = tmp[0] * 2;
//		if (tmp[1] > -y)
//		{
//			tmp[0] -= y;
//			data->x_cur += sx;
//		}
//		if (tmp[1] < x)
//		{
//			tmp[0] += x;
//			data->y_cur += sy;
//		}
//	}
//}

//void	xiaoline(t_data *data, double dx, double dy)
//{
//	t_bool	steep;
//	double	gradient;
//	steep = fabs(data->y_end - data->y_start) > fabs(data->x_end - data->x_start);
//	if (steep == TRUE)
//		dd_swap(&data->x_start, &data->y_start, &data->x_end, &data->y_end);
//	if (data->x_start > data->x_end)
//		dd_swap(&data->x_start, &data->x_end, &data->y_start, &data->y_end);
//	dx = data->x_end - data->x_start;
//	dy = data->y_end - data->y_start;
//	if (dx == 0.0)
//		gradient = 1.0;
//	else
//		gradient = dy / dx;
//	int xend = (int)floor(data->x_start + 0.5);
//	double yend = (int)(data->y_start + gradient * (xend - data->x_start));
//	double xgap = rf_part(data->x_start + 0.5);
//	int xpxl1 = xend;
//	int ypxl1 = (int)floor(yend);
//	if (steep == TRUE)
//	{
//		plot_dot(data, ypxl1, xpxl1, calc_color(rf_part(yend) * xgap));
//		plot_dot(data, ypxl1 + 1, xpxl1, calc_color(f_part(yend) * xgap));
//	}
//	else
//	{
//		plot_dot(data, xpxl1, ypxl1, calc_color(rf_part(yend) * xgap));
//		plot_dot(data, xpxl1, ypxl1 + 1, calc_color(f_part(yend) * xgap));
//	}
//	double intery = yend + gradient;
//
//	xend = (int)floor(data->x_end + 0.5);
//	yend = (int)(data->y_end + gradient * (xend - data->x_end));
//	xgap = f_part(data->x_end + 0.5);
//	int xpxl2 = xend;
//	int ypxl2 = (int)floor(yend);
//	if (steep == TRUE)
//	{
//		plot_dot(data, ypxl2, xpxl2, calc_color(rf_part(yend) * xgap));
//		plot_dot(data, ypxl2 + 1, xpxl2, calc_color(f_part(yend) * xgap));
//	}
//	else
//	{
//		plot_dot(data, xpxl2, ypxl2, calc_color(rf_part(yend) * xgap));
//		plot_dot(data, xpxl2, ypxl2 + 1, calc_color(f_part(yend) * xgap));
//	}
//	if (steep == TRUE)
//	{
//		for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
//		{
//			plot_dot(data, (int)floor(intery), x, calc_color(rf_part(intery)));
//			plot_dot(data, (int)floor(intery) + 1, x, calc_color(f_part(intery)));
//			intery = intery + gradient;
//		}
//	}
//	else
//	{
//		for (int x = xpxl1 + 1; x < xpxl2 - 1; x++)
//		{
//			plot_dot(data, x, (int)floor(intery), calc_color(rf_part(intery)));
//			plot_dot(data, x, (int)floor(intery) + 1, calc_color(f_part(intery)));
//			intery = intery + gradient;
//		}
//	}
//}

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
//				ft_draw_line(data, 0, 0);
				xiaoline(data, 0, 0);
			}
			if (y < data->height - 1)
			{
				set_start(data, x, y);
				set_end(data, x, y + 1);
//				ft_draw_line(data, 0, 0);
				xiaoline(data, 0, 0);
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
