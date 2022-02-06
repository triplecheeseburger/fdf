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
	if (0 < x + y * data->size_ln / 4
		&& x + y * data->size_ln / 4 < WIDTH * HEIGHT)
		data->addr[x + y * data->size_ln / 4] = data->clr_cur;
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
				xiaoline(data, 0, 0);
			}
			if (y < data->height - 1)
			{
				set_start(data, x, y);
				set_end(data, x, y + 1);
				xiaoline(data, 0, 0);
			}
		}
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 0, 0);
}
