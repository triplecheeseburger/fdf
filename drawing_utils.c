/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:25:20 by hakim             #+#    #+#             */
/*   Updated: 2022/02/06 19:25:25 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
