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

static void	draw_background(t_data *data)
{
	int	index;

	index = -1;
	while (++index < WIDTH * HEIGHT)
		data->addr[index] = 0x0A0A0A;
}

static void	draw_menu(t_data *data)
{
	int		index;

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

static void	menu_string_put(t_data *data)
{
	void	*m;
	void	*w;

	m = data->mlx;
	w = data->window;
	mlx_string_put(m, w, 65, 25, 0xFFFFFF, "HAPPY FDF!");
	mlx_string_put(m, w, 40, 50, 0xFFFFFF, "Menu Toggle: M");
	if (data->menu == FALSE)
		return ;
	mlx_string_put(m, w, 40, 110, 0xFFFFFF, "PROJECTION");
	mlx_string_put(m, w, 40, 130, 0xFFFFFF, "I: ISOMETRIC");
	mlx_string_put(m, w, 40, 150, 0xFFFFFF, "O: DIMETRIC");
	mlx_string_put(m, w, 40, 170, 0xFFFFFF, "P: PARALLEL");
	mlx_string_put(m, w, 40, 190, 0xFFFFFF, "[: TRIMETRIC");
	mlx_string_put(m, w, 40, 230, 0xFFFFFF, "ROTATE X / Y / Z");
	mlx_string_put(m, w, 40, 250, 0xFFFFFF, "E-R / D-F / C-V");
	mlx_string_put(m, w, 40, 290, 0xFFFFFF, "COLOR MODE: G / H");
	mlx_string_put(m, w, 40, 310, 0xFFFFFF, "ANTIALIASING: TAB / T");
	mlx_string_put(m, w, 40, 350, 0xFFFFFF, "ZDEPTH: 9/0 | ZOOM: -/+");
	mlx_string_put(m, w, 40, 390, 0xFFFFFF, "ADJUST R / G / B");
	mlx_string_put(m, w, 40, 410, 0xFFFFFF, "Q-W / A-S / Z-X");
	mlx_string_put(m, w, 40, 430, 0xFFFFFF, "ADJUST GRADATION: 1/2");
	mlx_string_put(m, w, 40, 470, 0xFFFFFF, "MOVE: ARROWS");
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
	menu_string_put(data);
}
