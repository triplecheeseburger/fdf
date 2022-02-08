/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakim <hakim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 00:35:48 by hakim             #+#    #+#             */
/*   Updated: 2022/02/05 00:35:50 by hakim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# define WIDTH 1400
# define HEIGHT 900
# define MENU 300
# define TRUE 1
# define FALSE 0

typedef enum s_err
{
	OPEN_ERR,
	MALLOC_ERR
}	t_err;

typedef enum s_projection
{
	PARALLEL,
	ISOMETRIC,
	DIMETRIC,
	TRIMETRIC
}	t_projection;

typedef struct s_data
{
	void	*mlx;
	void	*window;
	void	*img;
	int		**map;
	int		**color_map;
	int		*addr;
	int		bpp;
	int		size_ln;
	int		endian;
	int		menu;
	int		anti;
	int		tflag;
	int		cflag;
	int		pflag;
	int		zflag;
	int		projection;
	int		color;
	int		width;
	int		height;
	int		swapped;
	double	grad;
	double	x_st;
	double	y_st;
	double	z_st;
	double	x_cur;
	double	y_cur;
	double	z_cur;
	double	x_ed;
	double	y_ed;
	double	z_ed;
	int		clr_st;
	int		clr_cur;
	int		clr_ed;
	int		z_min;
	int		z_max;
	int		z_gap;
	double	angle;
	double	z_rad;
	double	x_ang;
	double	y_ang;
	double	z_ang;
	double	zoom;
	double	zoom_init;
	double	zdepth;
	double	x_shift;
	double	y_shift;
}	t_data;

typedef struct s_line
{
	double	gradient;
	double	xend;
	double	yend;
	double	gap;
}	t_line;

typedef int	t_bool;

int		key_press(int keycode, t_data *data);

void	fill_map(char *mappath, t_data *data);
void	fill_color_map(char **splitted, t_data *data, int row);

void	draw_image(t_data *data, int x, int y);
void	plot(t_data *data, int x, int y, double c);
void	get_color(t_data *data, double c);
void	get_preset_color(t_data *data, double z_cur, int *color);
void	get_default_color(t_data *data, double z_cur, int *color);

void	xiaoline(t_data *data, double dx, double dy);
void	dda(t_data *data, double dx, double dy);

void	select_projection(t_data *data, double *x, double *y, double *z);
void	set_start(t_data *data, int x, int y);
void	set_end(t_data *data, int x, int y);

double	f_part(double x);
double	rf_part(double x);
int		fdf_toggle(int button);

void	error(int mode);
void	*ft_free_int(int *arr);
void	*ft_free_str(char *str);
void	*ft_free_splitted(char **splitted);

#endif
