/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:41:29 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:41:32 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot(t_data *data, int x, int y, double c)
{
	get_color(data, c);
	if (0 <= x && x < WIDTH \
		&& 0 <= y && y < WIDTH * HEIGHT / (data->size_ln / 4))
		data->addr[x + y * data->size_ln / 4] = data->clr_cur;
}

static void	draw_background(t_data *data)
{
	int	index;

	index = -1;
	while (++index < WIDTH * HEIGHT)
		data->addr[index] = 0x0A0A0A;
}

static void	draw_menu(t_data *data)
{
	int	index;

	index = -1;
	while (++index < WIDTH * HEIGHT)
	{
		if (index % (data->size_ln / 4) < MENU)
			data->addr[index] = 0x061418;
	}
}

static void	draw_line(t_data *data)
{
	if (data->anti == TRUE)
		xiaoline(data, 0, 0);
	else
		dda(data, 0, 0);
}

void	draw_image(t_data *data, int x, int y)
{
	draw_background(data);
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
	if (data->menu == TRUE)
		draw_menu(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
