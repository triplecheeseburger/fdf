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

static double	get_percent(double start, double end, double current)
{
	double	offset;
	double	distance;

	offset = current - start;
	distance = end - start;
	if (0 <= distance && distance < 0.0001)
		return (1.0);
	return (offset / distance);
}

static int	calc_color(int clr_cur, double c)
{
	int	color;
	int	r;
	int	g;
	int	b;

	r = (int)(c * (clr_cur >> 16 & 0xFF));
	if (r > 255)
		r = 255;
	g = (int)(c * (clr_cur >> 8 & 0xFF));
	if (g > 255)
		g = 255;
	b = (int)(c * (clr_cur & 0xFF));
	if (b > 255)
		b = 255;
	color = r << 16;
	color += g << 8;
	color += b;
	return (color);
}

void	get_preset_color(t_data *data, double z_cur, int *color)
{
	double	percent;

	percent = get_percent(data->z_min, data->z_max, z_cur);
	if (percent < 0.2)
		*color = 0x00CCFF;
	else if (percent < 0.4)
		*color = 0xCC3333;
	else if (percent < 0.6)
		*color = 0x33FF00;
	else if (percent < 0.8)
		*color = 0xFFFFCC;
	else
		*color = 0xEF8633;
}

void	get_default_color(t_data *data, double z_cur, int *color)
{
	double	percent;

	z_cur = z_cur * data->grad / (data->zoom / data->zdepth) \
		+ (data->z_gap) * (1 - data->grad);
	percent = get_percent(data->z_min, data->z_max, z_cur);
	*color = calc_color(data->color, percent);
}

void	get_color(t_data *data, double c)
{
	int		r;
	int		g;
	int		b;
	double	perc;

	if (fabs(data->x_ed - data->x_st) > fabs(data->y_ed - data->y_st))
		perc = get_percent(data->x_st, data->x_ed, data->x_cur);
	else
		perc = get_percent(data->y_st, data->y_ed, data->y_cur);
	if (data->z_st < data->z_ed)
		perc = 1 - perc;
	r = (1.0 - perc) * ((data->clr_st >> 16) & 0xFF) \
		+ ((data->clr_ed >> 16) & 0xFF) * perc;
	g = (1.0 - perc) * ((data->clr_st >> 8) & 0xFF) \
		+ ((data->clr_ed >> 8) & 0xFF) * perc;
	b = (1.0 - perc) * (data->clr_st & 0xFF) \
		+ (data->clr_ed & 0xFF) * perc;
	data->clr_cur = (r << 16) + (g << 8) + b;
	calc_color(data->clr_cur, c);
}
