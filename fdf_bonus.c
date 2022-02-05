/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:41 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 22:19:23 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_image(t_data *data)
{
	for (int i = 0; i < 500; i++)
	{
		for (int j = 0; j < 500; j++)
			data->data[i * 500 + j] = 0xFFFFFF;
	}
	mlx_put_image_to_window(data->mlx, data->window, data->img, 450, 200);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 53)
		exit(0);
	draw_image(data);
	return (0);
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
	print_ori_map(&data);
	print_cur_map(&data);
	print_color_map(&data);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, 1400, 900, "FDF");
	mlx_hook(data.window, 2, 0, key_press, &data);
	data.img = mlx_new_image(data.mlx, 500, 500);
	data.data = (int *)mlx_get_data_addr(data.img, &data.bpp, &data.size_line, &data.endian);
	draw_image(&data);
	mlx_loop(data.mlx);
}
