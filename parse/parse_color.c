/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:51:28 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 17:51:29 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_strchr_idx(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		if (s[index] == (unsigned char)c)
			return (index);
		++index;
	}
	if ((unsigned char)c == '\0')
		return (index);
	return (-1);
}

static int	extract_color(char *info)
{
	int	index;
	int	result;

	index = 0;
	result = 0;
	while (info[index] != '\0' && info[index] != ',')
		++index;
	if (info[index] == '\0')
		return (0xFFFFFF);
	if (info[index] == ',')
		++index;
	if (info[index] == '0')
		++index;
	if (info[index] == 'x')
		++index;
	while (info[index] != '\0')
	{
		result *= 16;
		result += ft_strchr_idx("0123456789ABCDEF", info[index]);
		++index;
	}
	return (result);
}

void	fill_color_map(char **splitted, t_data *data, int row)
{
	int	index;

	index = -1;
	while (splitted[++index] != 0)
		data->color_map[row][index] = extract_color(splitted[index]);
}
