/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:44:52 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:44:53 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_axis_xyz(double *y, double *z, double x_ang)
{
	double	temp_y;

	temp_y = *y;
	*y = temp_y * cos(x_ang) + *z * sin(x_ang);
	*z = -temp_y * sin(x_ang) + *z * cos(x_ang);
}

static void	adjust_gap(t_data *data, double *x, double *y)
{
	double	x_center;
	double	y_center;
	double	z_center;
	double	y_adjust;

	x_center = data->width / 2.0;
	y_center = data->height / 2.0;
	z_center = data->map[(int)y_center][(int)x_center];
	select_projection(data, &x_center, &y_center, &z_center);
	if (y_center > data->z_gap)
		y_adjust = y_center;
	else
		y_adjust = (y_center + data->z_gap) / 10.0;
	if (data->projection != PARALLEL)
	{
		*x += WIDTH / 2.0 - x_center * data->zoom + data->x_shift;
		*y += HEIGHT / 2.0 - y_adjust * data->zoom + data->y_shift;
	}
	else
	{
		*x += (WIDTH - data->width * data->zoom) / 2.0 + data->x_shift;
		*y += (HEIGHT - data->height * data->zoom) / 2.0 + data->y_shift;
	}
}

static double	get_zoom(t_data *data)
{
	double	zoom;

	if (data->zoom >= 1)
	{
		zoom = (int)data->zoom;
		data->zflag = FALSE;
	}
	else
	{
		zoom = data->zoom;
		data->zflag = TRUE;
	}
	return (zoom);
}

void	set_start(t_data *data, int x, int y)
{
	double	zoom;

	zoom = get_zoom(data);
	data->x_st = x * zoom;
	data->y_st = y * zoom;
	data->z_st = data->map[y][x] * zoom / data->zdepth;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_st, &data->clr_st);
	else if (data->cflag == FALSE && data->pflag == TRUE)
		get_preset_color(data, data->z_st, &data->clr_st);
	else
		data->clr_st = data->color_map[y][x];
	rotate_axis_xyz(&data->y_st, &data->z_st, data->x_ang);
	rotate_axis_xyz(&data->x_st, &data->z_st, data->y_ang);
	rotate_axis_xyz(&data->x_st, &data->y_st, data->z_ang);
	if (data->projection != PARALLEL)
		select_projection(data, &data->x_st, &data->y_st, &data->z_st);
	adjust_gap(data, &data->x_st, &data->y_st);
	data->x_cur = data->x_st;
	data->y_cur = data->y_st;
	data->z_cur = data->z_st;
	data->clr_cur = data->clr_st;
}

void	set_end(t_data *data, int x, int y)
{
	double	zoom;

	zoom = get_zoom(data);
	data->x_ed = x * zoom;
	data->y_ed = y * zoom;
	data->z_ed = data->map[y][x] * zoom / data->zdepth;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_ed, &data->clr_ed);
	else if (data->cflag == FALSE && data->pflag == TRUE)
		get_preset_color(data, data->z_ed, &data->clr_ed);
	else
		data->clr_ed = data->color_map[y][x];
	rotate_axis_xyz(&data->y_ed, &data->z_ed, data->x_ang);
	rotate_axis_xyz(&data->x_ed, &data->z_ed, data->y_ang);
	rotate_axis_xyz(&data->x_ed, &data->y_ed, data->z_ang);
	if (data->projection != PARALLEL)
		select_projection(data, &data->x_ed, &data->y_ed, &data->z_ed);
	adjust_gap(data, &data->x_ed, &data->y_ed);
}
