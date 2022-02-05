/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:48 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 22:19:20 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

typedef enum s_err
{
	OPEN_ERR,
	MALLOC_ERR
}	t_err;

typedef enum s_projection
{
	ISOMETRIC,
	PARALLEL,
	CONIC
}	t_projection;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	int 	**ori_map;
	int 	**cur_map;
	int 	**color_map;
	int 	*data;
	int 	bpp;
	int 	size_line;
	int 	endian;
	int 	width;
	int 	height;
	double	angle;
}	t_data;

void	fill_map(char *mappath, t_data *data);
void	fill_color_map(char **splitted, t_data *data, int row);

void	copy_map(int **src_map, int **dst_map, t_data *data);

void	error(int mode);
void	*ft_free_int(int *arr);
void	*ft_free_str(char *str);
void	*ft_free_splitted(char **splitted);

/* for test */
void	print_cur_map(t_data *data);
void	print_ori_map(t_data *data);
void	print_color_map(t_data *data);

#endif
