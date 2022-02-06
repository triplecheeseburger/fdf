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

/*
void	ft_draw_line(t_data *data, int sx, int sy)
{
}
*/
int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	init_data(&data);
	fill_map(av[1], &data);
	print_map(&data);
	print_color_map(&data);
	printf("%d\n", data.cflag);
	data.mlx = mlx_init();
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FDF");
	mlx_hook(data.window, 2, 0, key_press, &data);
	mlx_hook(data.window, 17, 0, red_button, 0);
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = (int *)mlx_get_data_addr(data.img,
			&data.bpp, &data.size_ln, &data.endian);
	draw_image(&data);
	mlx_loop(data.mlx);
}
