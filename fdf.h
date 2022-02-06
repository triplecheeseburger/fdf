/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:48 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 00:35:50 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# define WIDTH 1400
# define HEIGHT 900
# define ZOOM 25
# define TRUE 1
# define FALSE 0
# define ZDEPTH 3

typedef enum s_err
{
	OPEN_ERR,
	MALLOC_ERR
}	t_err;

typedef enum s_direction
{
	VERTICAL,
	HORIZONTAL
}	t_direction;

typedef enum s_projection
{
	ISOMETRIC,
	PARALLEL,
	CONIC
}	t_projection;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	int 	**map;
	int 	**color_map;
	int 	*addr;
	int 	bpp;
	int 	size_ln;
	int 	endian;
	int		cflag;
	int 	width;
	int 	height;
	double 	x_st;
	double 	y_st;
	double 	z_st;
	int		clr_st;
	double 	x_cur;
	double	y_cur;
	double	z_cur;
	int 	clr_cur;
	double	x_ed;
	double	y_ed;
	double	z_ed;
	int		clr_ed;
	double	angle;
	int 	z_min;
	int 	z_max;
}	t_data;

typedef struct s_line
{
	double	gradient;
	double	xend;
	double	yend;
	double	gap;
}	t_line;

typedef int t_bool;

int		key_press(int keycode);
int		red_button(int exitcode);

void	fill_map(char *mappath, t_data *data);
void	fill_color_map(char **splitted, t_data *data, int row);

void	draw_image(t_data *data);
void	plot(t_data *data, int x, int y, double c);
void	get_color(t_data *data, double c);
void	get_default_color(t_data *data, double z_cur, int *color);
void	xiaoline(t_data *data, double dx, double dy);

void	project_isometric(double *x, double *y, double *z);
void	init_data(t_data *data);
void	set_start(t_data *data, int x, int y);
void	set_end(t_data *data, int x, int y);

int		ft_abs(int n);
double	f_part(double x);
double	rf_part(double x);

void	error(int mode);
void	*ft_free_int(int *arr);
void	*ft_free_str(char *str);
void	*ft_free_splitted(char **splitted);

/* for test */
void	print_map(t_data *data);
void	print_color_map(t_data *data);

#endif
/*

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
//	if (data->clr_cur == data->clr_ed)
//		return (data->clr_cur);
//	if (x > y)
//		percent = ft_percent(data->x_st, data->x_ed, data->x_cur);
//	else
//		percent = get_percent(data->y_st, data->y_ed, data->y_cur);
//	r = ft_get_light((data->clr_st >> 16) & 0xFF, (data->clr_ed >> 16)
//												& 0xFF, percent);
//	g = ft_get_light((data->clr_st >> 8) & 0xFF, (data->clr_ed >> 8)
//											   & 0xFF, percent);
//	b = get_grade(data->clr_st & 0xFF, data->clr_ed & 0xFF, percent);
//	return (((r << 16) | (g << 8) | b));
//}
//
//static void	ft_draw_line(t_data *data, int sx, int sy)
//{
//	int	x;
//	int	y;
//	int	tmp[2];
//
//	x = ft_abs(data->x_ed - data->x_st);
//	y = ft_abs(data->y_ed - data->y_st);
//	sx = ft_comper(data->x_st, data->x_ed);
//	sy = ft_comper(data->y_st, data->y_ed);
//	tmp[0] = x - y;
//	while (0 < (int)(data->x_cur + data->y_cur * data->size_ln / 4) && (int)(data->x_cur + data->y_cur * data->size_ln / 4) < WIDTH * HEIGHT)
//	{
//		data->clr_cur = get_color(data, x, y);
//		data->addr[(int)(data->x_cur + data->y_cur * data->size_ln / 4)] = data->clr_cur;
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
//	steep = fabs(data->y_ed - data->y_st) > fabs(data->x_ed - data->x_st);
//	if (steep == TRUE)
//		dd_swap(&data->x_st, &data->y_st, &data->x_ed, &data->y_ed);
//	if (data->x_st > data->x_ed)
//		dd_swap(&data->x_st, &data->x_ed, &data->y_st, &data->y_ed);
//	dx = data->x_ed - data->x_st;
//	dy = data->y_ed - data->y_st;
//	if (dx == 0.0)
//		gradient = 1.0;
//	else
//		gradient = dy / dx;
//	int xend = (int)floor(data->x_st + 0.5);
//	double yend = (int)(data->y_st + gradient * (xend - data->x_st));
//	double xgap = rf_part(data->x_st + 0.5);
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
//	xend = (int)floor(data->x_ed + 0.5);
//	yend = (int)(data->y_ed + gradient * (xend - data->x_ed));
//	xgap = f_part(data->x_ed + 0.5);
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

void	when_dx_greater(t_data *data, t_line *line, double dx, double dy)
{
	if (data->x_ed < data->x_st)
		dd_swap(&data->x_st, &data->x_ed, &data->y_st, &data->y_ed);
	line->gradient = dy / dx;
	data->x_cur = (int)(data->x_st + 0.5);
	data->y_cur = data->y_st + line->gradient * (data->x_cur - data->x_st);
	line->gap = rf_part(data->x_st + 0.5);
	plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->y_cur) * gap));
	plot_dot(data, data->x_cur, data->y_cur + 1, calc_color(data, f_part(data->y_cur) * gap));
	data->y_cur += line->gradient;
	line->xend = (int)(data->x_ed + 0.5);
	line->yend = data->y_ed + line->gradient * (line->xend - data->x_ed);
	line->gap = f_part(data->x_ed + 0.5);
//		plot(data, xend, yend, calc_color(data, rf_part(yend) * line->gap));
//		plot_dot(data, xend, yend + 1, calc_color(data, f_part(yend) * line->gap));
	while (data->x_cur++ < line->xend)
	{
		get_color(data);
		plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->y_cur)));
		plot_dot(data, data->x_cur, data->y_cur + 1, calc_color(data, f_part(data->y_cur)));
		data->y_cur += line->gradient;
	}
}

void	when_dx_lesser(t_data *data, t_line *line, double dx, double dy)
{
	if (data->y_ed < data->y_st)
		dd_swap(&data->x_st, &data->x_ed, &data->y_st, &data->y_ed);
	line->gradient = dx / dy;
	data->y_cur = (int)(data->y_st + 0.5);
	data->x_cur = data->x_st + line->gradient * (data->y_cur - data->y_st);
	line->gap = rf_part(data->y_st + 0.5);
	plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->y_cur) * gap));
	plot_dot(data, data->x_cur + 1, data->y_cur, calc_color(data, f_part(data->y_cur) * gap));
	data->x_cur += line->gradient;
	line->yend = (int)(data->y_ed + 0.5);
	line->xend = data->y_ed + line->gradient * (line->yend - data->x_ed);
	line->gap = f_part(data->y_ed + 0.5);
//		plot_dot(data, xend, yend, calc_color(data, rf_part(xend) * gap));
//		plot_dot(data, xend + 1, yend, calc_color(data, f_part(xend) * gap));
	while (data->y_cur++ < line->yend)
	{
		get_color(data);
		plot_dot(data, data->x_cur, data->y_cur, calc_color(data, rf_part(data->x_cur)));
		plot_dot(data, data->x_cur + 1, data->y_cur, calc_color(data, f_part(data->x_cur)));
		data->x_cur += line->gradient;
	}
}

 */


