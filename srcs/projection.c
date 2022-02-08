/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:45:28 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:45:29 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	project_isometric(double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(0.523599));
	*y = ((prev_x + prev_y) * sin(0.523599) - *z);
}

static void	project_dimetric(double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(0.261799));
	*y = ((prev_x + prev_y) * sin(0.261799) - *z);
}

static void	project_trimetric(double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = ((prev_x - prev_y) * cos(0.261799));
	*y = ((prev_x + prev_y) * sin(0.785398) - *z);
}

void	select_projection(t_data *data, double *x, double *y, double *z)
{
	if (data->projection == ISOMETRIC)
		project_isometric(x, y, z);
	if (data->projection == DIMETRIC)
		project_dimetric(x, y, z);
	if (data->projection == TRIMETRIC)
		project_trimetric(x, y, z);
}
