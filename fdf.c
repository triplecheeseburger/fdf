/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:41 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 14:36:01 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_data(t_data *data)
{
	data->width = 0;
	data->height = 0;
	data->anti = FALSE;
	data->tflag = FALSE;
	data->cflag = FALSE;
	data->pflag = FALSE;
	data->menu = FALSE;
	data->color = 0xFFFFFF;
	data->z_min = 2147483647;
	data->z_max = -2147483648;
	data->zdepth = 1;
	data->x_shift = 0;
	data->y_shift = 0;
	data->grad = 0.8;
	data->projection = ISOMETRIC;
	data->x_ang = 0;
	data->y_ang = 0;
	data->z_ang = 0;
	data->swapped = FALSE;
}

static void	init_data_sequal(t_data *data)
{
	data->z_gap = data->z_max - data->z_min;
	data->zoom = 30;
	while ((data->width + data->z_gap) * data->zoom \
		* (data->height + data->z_gap) * data->zoom \
		> (WIDTH + 20 * data->zoom) * (HEIGHT + 20 * data->zoom) / 3.0)
	{
		if (data->zoom > 1)
			data->zoom -= 1;
	}
}

int	red_button(int exitcode)
{
	exit(exitcode);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	init_data(&data);
	fill_map(av[1], &data);
	init_data_sequal(&data);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FDF");
	mlx_hook(data.window, 2, 0, key_press, &data);
	mlx_hook(data.window, 17, 0, red_button, 0);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = (int *)mlx_get_data_addr(data.img,
			&data.bpp, &data.size_ln, &data.endian);
	draw_image(&data, 0, 0);
	mlx_loop(data.mlx);
}
