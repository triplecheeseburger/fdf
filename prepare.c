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

void	init_data(t_data *data)
{
	data->width = 0;
	data->height = 0;
	data->cflag = TRUE;
	data->z_min = 2147483647;
	data->z_max = -2147483648;
}

void	set_start(t_data *data, int x, int y)
{
	data->x_st = x * ZOOM;
	data->y_st = y * ZOOM;
	data->z_st = data->map[y][x] * ZOOM / ZDEPTH;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_st, &data->clr_st);
	else
		data->clr_st = data->color_map[y][x];
	data->x_st -= (data->width * ZOOM) / 2.0;
	data->y_st -= (data->height * ZOOM) / 2.0;
	project_isometric(&data->x_st, &data->y_st, &data->z_st);
	data->x_st += WIDTH / 2.0;
	data->y_st += (HEIGHT + data->height * ZOOM) / 2.0;
	data->x_cur = data->x_st;
	data->y_cur = data->y_st;
	data->z_cur = data->z_st;
	data->clr_cur = data->clr_st;
}

void	set_end(t_data *data, int x, int y)
{
	data->x_ed = x * ZOOM;
	data->y_ed = y * ZOOM;
	data->z_ed = data->map[y][x] * ZOOM / ZDEPTH;
	if (data->cflag == TRUE)
		get_default_color(data, data->z_ed, &data->clr_ed);
	else
		data->clr_ed = data->color_map[y][x];
	data->x_ed -= (data->width * ZOOM) / 2.0;
	data->y_ed -= (data->height * ZOOM) / 2.0;
	project_isometric(&data->x_ed, &data->y_ed, &data->z_ed);
	data->x_ed += WIDTH / 2.0;
	data->y_ed += (HEIGHT + data->height * ZOOM) / 2.0;
}
