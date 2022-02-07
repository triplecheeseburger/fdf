/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:27:24 by hakim             #+#    #+#             */
/*   Updated: 2022/02/07 15:27:25 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int ft_compare(double a, double b)
{
	if (a < b)
		return (1);
	return (-1);
}

void	bresenham(t_data *data, double dx, double dy)
{
	int		x_step;
	int		y_step;
	double	tmp[2];

	dx = fabs(data->x_ed - data->x_st);
	dy = fabs(data->y_ed - data->y_st);
	x_step = ft_compare(data->x_st, data->x_ed);
	y_step = ft_compare(data->y_st, data->y_ed);
	tmp[0] = dx - dy;
	while (fabs(data->x_cur - data->x_ed) > 0.1 \
		&& fabs(data->y_cur - data->y_ed) > 0.1)
	{
		plot(data, data->x_cur, data->y_cur, 1);
		tmp[1] = tmp[0] * 2;
		if (tmp[1] > -dy)
		{
			tmp[0] -= dy;
			data->x_cur += x_step;
		}
		if (tmp[1] < dx)
		{
			tmp[0] += dx;
			data->y_cur += y_step;
		}
	}
}