/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:25:20 by hakim             #+#    #+#             */
/*   Updated: 2022/02/09 03:44:49 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	plot(t_data *data, int x, int y, double c)
{
	get_color(data, c);
	if (0 <= x && x < WIDTH \
		&& 0 <= y && y < WIDTH * HEIGHT / (data->size_ln / 4))
		data->addr[x + y * data->size_ln / 4] = data->clr_cur;
}

double	f_part(double x)
{
	return (x - floor(x));
}

double	rf_part(double x)
{
	return (1 - f_part(x));
}

int	fdf_toggle(int button)
{
	if (button == TRUE)
		return (FALSE);
	return (TRUE);
}
