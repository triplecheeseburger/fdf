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

static void	rotate_axis_x(double *y, double *z, double x_ang)
{
	double	temp_y;

	temp_y = *y;
	*y = temp_y * cos(x_ang) + *z * sin(x_ang);
	*z = -temp_y * sin(x_ang) + *z * cos(x_ang);
}

static void	rotate_axis_y(double *x, double *z, double y_ang)
{
	double	temp_x;

	temp_x = *x;
	*x = temp_x * cos(y_ang) + *z * sin(y_ang);
	*z = -temp_x * sin(y_ang) + *z * cos(y_ang);
}

static void	rotate_axis_z(double *x, double *y, double z_ang)
{
	double	temp_x;
	double	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(z_ang) - temp_y * sin(z_ang);
	*y = temp_x * sin(z_ang) + temp_y * cos(z_ang);
}

void	set_start(t_data *data, int x, int y)
{
	data->x_st = x * data->zoom;
	data->y_st = y * data->zoom;
	data->z_st = data->map[y][x] * data->zoom / data->zdepth;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_st, &data->clr_st);
	else if (data->cflag == FALSE && data->pflag == TRUE)
		get_preset_color(data, data->z_st, &data->clr_st);
	else
		data->clr_st = data->color_map[y][x];
	data->x_st -= ((data->width + data->z_gap) * data->zoom) / 2.0;
	data->y_st -= ((data->height + data->z_gap) * data->zoom) / 2.0;
	rotate_axis_x(&data->y_st, &data->z_st, data->x_ang);
	rotate_axis_y(&data->x_st, &data->z_st, data->y_ang);
	rotate_axis_z(&data->x_st, &data->y_st, data->z_ang);
	if (data->projection != PARALLEL)
		select_projection(data, &data->x_st, &data->y_st, &data->z_st);
	data->x_st += WIDTH / 2.0 + data->x_shift;
	data->y_st += (HEIGHT + (data->z_gap) * data->zoom) / 2.0 + data->y_shift;
	data->x_cur = data->x_st;
	data->y_cur = data->y_st;
	data->z_cur = data->z_st;
	data->clr_cur = data->clr_st;
}

void	set_end(t_data *data, int x, int y)
{
	data->x_ed = x * data->zoom;
	data->y_ed = y * data->zoom;
	data->z_ed = data->map[y][x] * data->zoom / data->zdepth;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_ed, &data->clr_ed);
	else if (data->cflag == FALSE && data->pflag == TRUE)
		get_preset_color(data, data->z_ed, &data->clr_ed);
	else
		data->clr_ed = data->color_map[y][x];
	data->x_ed -= ((data->width + data->z_gap) * data->zoom) / 2.0;
	data->y_ed -= ((data->height + data->z_gap) * data->zoom) / 2.0;
	rotate_axis_x(&data->y_ed, &data->z_ed, data->x_ang);
	rotate_axis_y(&data->x_ed, &data->z_ed, data->y_ang);
	rotate_axis_z(&data->x_ed, &data->y_ed, data->z_ang);
	if (data->projection != PARALLEL)
		select_projection(data, &data->x_ed, &data->y_ed, &data->z_ed);
	data->x_ed += WIDTH / 2.0 + data->x_shift;
	data->y_ed += (HEIGHT + (data->z_gap) * data->zoom) / 2.0 + data->y_shift;
}
