/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:47:15 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:47:16 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	re_init_data(t_data *data)
{
	data->zoom = 30;
	while (WIDTH * data->zoom * HEIGHT * data->zoom > WIDTH * HEIGHT * 3)
		data->zoom /= 1.1;
	data->cflag = FALSE;
	data->pflag = FALSE;
	data->menu = FALSE;
	data->color = 0xFFFFFF;
	data->zdepth = 1;
	data->x_shift = 0;
	data->y_shift = 0;
	data->grad = 0.8;
	data->projection = ISOMETRIC;
	data->x_ang = 0;
	data->y_ang = 0;
	data->z_ang = 0;
}

static int	fdf_toggle(int button)
{
	if (button == TRUE)
		return (FALSE);
	return (TRUE);
}

static void	key_press3(int keycode, t_data *data)
{
	if (keycode == 34)
		data->projection = ISOMETRIC;
	if (keycode == 31)
		data->projection = DIMETRIC;
	if (keycode == 35)
		data->projection = PARALLEL;
	if (keycode == 33)
		data->projection = TRIMETRIC;
	if (keycode == 14)
		data->x_ang -= 0.1;
	if (keycode == 15)
		data->x_ang += 0.1;
	if (keycode == 2)
		data->y_ang -= 0.1;
	if (keycode == 3)
		data->y_ang += 0.1;
	if (keycode == 8)
		data->z_ang -= 0.1;
	if (keycode == 9)
		data->z_ang += 0.1;
}

static void	key_press2(int keycode, t_data *data)
{
	if (keycode == 46)
		data->menu = fdf_toggle(data->menu);
	if (keycode == 5)
		data->cflag = fdf_toggle(data->cflag);
	if (keycode == 4)
		data->pflag = fdf_toggle(data->pflag);
	if (keycode == 48)
		data->anti = fdf_toggle(data->anti);
	if (keycode == 12 && (data->color >> 16 & 0xFF) < 251)
		data->color += 8 << 16;
	if (keycode == 13 && (data->color >> 16 & 0xFF) > 4)
		data->color -= 8 << 16;
	if (keycode == 0 && (data->color >> 8 & 0xFF) < 251)
		data->color += 8 << 8;
	if (keycode == 1 && (data->color >> 8 & 0xFF) > 4)
		data->color -= 8 << 8;
	if (keycode == 6 && (data->color & 0xFF) < 251)
		data->color += 8;
	if (keycode == 7 && (data->color & 0xFF) > 4)
		data->color -= 8;
	if (keycode == 18 && data->grad < 0.95)
		data->grad += 0.02;
	if (keycode == 19 && data->grad > 0.05)
		data->grad -= 0.02;
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 51)
		re_init_data(data);
	if (keycode == 123)
		data->x_shift += 15;
	if (keycode == 124)
		data-> x_shift -= 15;
	if (keycode == 125)
		data->y_shift -= 15;
	if (keycode == 126)
		data->y_shift += 15;
	if (keycode == 27)
		data->zoom /= 1.1;
	if (keycode == 24)
		data->zoom *= 1.1;
	if (keycode == 25 && data->zdepth > 1)
		data->zdepth -= 1;
	if (keycode == 29)
		data->zdepth += 1;
	key_press2(keycode, data);
	key_press3(keycode, data);
	draw_image(data, 0, 0);
	return (0);
}
