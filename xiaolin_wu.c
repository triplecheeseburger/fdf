/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolin_wu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:19:39 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:19:42 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	dd_swap(double *a, double *b, double *c, double *d)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
	temp = *c;
	*c = *d;
	*d = temp;
}

static void	when_dx_greater(t_data *data, t_line *line, double dx, double dy)
{
	if (data->x_ed < data->x_st)
		dd_swap(&data->x_st, &data->x_ed, &data->y_st, &data->y_ed);
	line->gradient = dy / dx;
	data->x_cur = (int)(data->x_st + 0.5);
	data->y_cur = data->y_st + line->gradient * (data->x_cur - data->x_st);
	line->gap = rf_part(data->x_st + 0.5);
	plot(data, data->x_cur, data->y_cur,
		rf_part(data->y_cur) * line->gap);
	plot(data, data->x_cur, data->y_cur + 1,
		f_part(data->y_cur) * line->gap);
	data->y_cur += line->gradient;
	line->xend = (int)(data->x_ed + 0.5);
	line->yend = data->y_ed + line->gradient * (line->xend - data->x_ed);
	line->gap = f_part(data->x_ed + 0.5);
	while (data->x_cur++ < line->xend)
	{
		plot(data, data->x_cur, data->y_cur, rf_part(data->y_cur));
		plot(data, data->x_cur, data->y_cur + 1, f_part(data->y_cur));
		data->y_cur += line->gradient;
	}
}

static void	when_dx_lesser(t_data *data, t_line *line, double dx, double dy)
{
	if (data->y_ed < data->y_st)
		dd_swap(&data->x_st, &data->x_ed, &data->y_st, &data->y_ed);
	line->gradient = dx / dy;
	data->y_cur = (int)(data->y_st + 0.5);
	data->x_cur = data->x_st + line->gradient * (data->y_cur - data->y_st);
	line->gap = rf_part(data->y_st + 0.5);
	plot(data, data->x_cur, data->y_cur, rf_part(data->y_cur) * line->gap);
	plot(data, data->x_cur + 1, data->y_cur, f_part(data->y_cur) * line->gap);
	data->x_cur += line->gradient;
	line->yend = (int)(data->y_ed + 0.5);
	line->xend = data->y_ed + line->gradient * (line->yend - data->x_ed);
	line->gap = f_part(data->y_ed + 0.5);
	while (data->y_cur++ < line->yend)
	{
		plot(data, data->x_cur, data->y_cur,
			rf_part(data->x_cur));
		plot(data, data->x_cur + 1, data->y_cur,
			f_part(data->x_cur));
		data->x_cur += line->gradient;
	}
}

void	xiaoline(t_data *data, double dx, double dy)
{
	t_line	line;

	line.gradient = 0;
	line.xend = 0;
	line.yend = 0;
	line.gap = 0;
	dx = data->x_ed - data->x_st;
	dy = data->y_ed - data->y_st;
	if (fabs(dx) > fabs(dy))
		when_dx_greater(data, &line, dx, dy);
	else
		when_dx_lesser(data, &line, dx, dy);
}
