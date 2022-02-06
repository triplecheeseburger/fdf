/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:23:16 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:23:16 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static double	get_percent(int start, int end, int current)
{
	double	plac;
	double	dist;

	plac = current - start;
	dist = end - start;
	if (dist == 0)
		return (1.0);
	return ((plac / dist));
}

static int	get_grade(int start, int end, double percent)
{
	return ((int)((1 - percent) * start + percent * end));
}

static int	calc_color(t_data *data, double c)
{
	int	color;
	int	r;
	int	g;
	int	b;

	r = (int)(c * (data->clr_cur >> 16 & 0xFF));
	if (r > 255)
		r = 255;
	g = (int)(c * (data->clr_cur >> 8 & 0xFF));
	if (g > 255)
		g = 255;
	b = (int)(c * (data->clr_cur & 0xFF));
	if (b > 255)
		b = 255;
	color = r << 16;
	color += g << 8;
	color += b;
	return (color);
}

void	get_default_color(t_data *data, double z_cur, int *color)
{
	double	percent;

	percent = get_percent(data->z_min, data->z_max, z_cur);
	if (percent < 0.2)
		*color = 0x66CC00;
	else if (percent < 0.4)
		*color = 0x99FF33;
	else if (percent < 0.51)
		*color = 0xB2FF66;
	else if (percent < 0.8)
		*color = 0xCCFF99;
	else
		*color = 0xE5FFCC;
}

void	get_color(t_data *data, double c)
{
	int		r;
	int		g;
	int		b;
	double	percent;

	if (data->clr_cur == data->clr_ed)
		return ;
	if (ft_abs(data->x_ed - data->x_st) > ft_abs(data->y_ed - data->y_st))
		percent = get_percent(data->x_st, data->x_ed, data->x_cur);
	else
		percent = get_percent(data->y_st, data->y_ed, data->y_cur);
	if (data->z_cur < data->z_ed)
		percent = 1 - percent;
	r = get_grade((data->clr_st >> 16) & 0xFF, (data->clr_ed >> 16)
			& 0xFF, percent);
	g = get_grade((data->clr_st >> 8) & 0xFF, (data->clr_ed >> 8)
			& 0xFF, percent);
	b = get_grade(data->clr_st & 0xFF, data->clr_ed & 0xFF, percent);
	data->clr_cur = (r << 16) + (g << 8) + b;
	calc_color(data, c);
}
