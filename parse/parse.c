/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:25:04 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 15:25:05 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	split_n_put(char *line, t_data *data, int row)
{
	char	**splitted;
	int		index;

	splitted = ft_split(line, ' ');
	if (splitted == 0)
		error(MALLOC_ERR);
	index = -1;
	while (++index < data->width)
		data->map[row][index] = ft_atoi(splitted[index]);
	fill_color_map(splitted, data, row);
	ft_free_splitted(splitted);
}

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	if (s == 0)
		return (0);
	i = 0;
	count = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (count);
}

static void	get_width_height(char *mappath, t_data *data)
{
	int		fd;
	char	*line;

	fd = open(mappath, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	line = get_next_line(fd);
	data->width = count_words(line, ' ');
	while (line != 0)
	{
		data->height++;
		ft_free_str(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	prepare_maps(int ***map, t_data *data)
{
	int	row;

	*map = malloc(sizeof(int *) * data->height);
	if (*map == 0)
		error(MALLOC_ERR);
	row = -1;
	while (++row < data->height)
	{
		(*map)[row] = malloc(sizeof(int) * data->width);
		if ((*map)[row] == 0)
			error(MALLOC_ERR);
	}
}

void	fill_map(char *mappath, t_data *data)
{
	int		fd;
	int		row;
	char	*line;

	get_width_height(mappath, data);
	prepare_maps(&data->map, data);
	prepare_maps(&data->color_map, data);
	fd = open(mappath, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	row = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == 0)
			break ;
		split_n_put(line, data, row++);
		ft_free_str(line);
	}
	close(fd);
}
