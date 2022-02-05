/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 18:42:52 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 18:42:52 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	copy_map(int **src_map, int **dst_map, t_data *data)
{
	int	row;

	row = -1;
	while (++row < data->height)
		ft_memcpy(dst_map[row], src_map[row], sizeof(int) * data->width);
}
