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
# define ZOOM 15
# define PADDING 200
typedef enum s_err
{
	OPEN_ERR,
	MALLOC_ERR
}	t_err;

typedef enum s_direction
{
	VERTICAL,
	HORIZONTAL
}	t_direction;

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
	int 	**map;
	int 	**color_map;
	int 	*addr;
	int 	bpp;
	int 	size_line;
	int 	endian;
	int 	width;
	int 	height;
	int 	x_start;
	int 	y_start;
	int 	z_start;
	int		color_start;
	int 	x_cur;
	int 	y_cur;
	int 	z_cur;
	int 	color_cur;
	int 	x_end;
	int 	y_end;
	int 	z_end;
	int		color_end;
	double	angle;
}	t_data;

typedef struct s_coord
{

}	t_coord;
void	fill_map(char *mappath, t_data *data);
void	fill_color_map(char **splitted, t_data *data, int row);

void	error(int mode);
void	*ft_free_int(int *arr);
void	*ft_free_str(char *str);
void	*ft_free_splitted(char **splitted);

/* for test */
void	print_map(t_data *data);
void	print_color_map(t_data *data);

#endif
/*
static void	ft_draw_line(t_data *data, int sx, int sy)
{
	int	x;
	int	y;
	int	tmp[2];

	x = ft_abs(data->end_x - data->st_x);
	y = ft_abs(data->end_y - data->st_y);
	sx = ft_comper(data->st_x, data->end_x);
	sy = ft_comper(data->st_y, data->end_y);
	tmp[0] = x - y;
	while (data->cur_x != data->end_x || data->cur_y != data->end_y)
	{
		data->cur_c = ft_get_color(data, x, y);
		ft_put_pixel(data, data->cur_x, data->cur_y);
		tmp[1] = tmp[0] * 2;
		if (tmp[1] > -y)
		{
			tmp[0] -= y;
			data->cur_x += sx;
		}
		if (tmp[1] < x)
		{
			tmp[0] += x;
			data->cur_y += sy;
		}
	}
}

  Algorithm Bresenham(x1, y1, x2, y2)
 {
    x = x1;
    y = y1;
    dx = x2 - x1
    dy = y2 - y1
    p = 2dy - dx
    while (x <= x2)
    {
    	put_pixel(x,y)
        x++
        if (p < 0)
        	p = p + 2dy
        else
       	{
        	p = p + 2dy - 2dx
            y++
	}
    }
 }

 static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

 function plot(x, y, c) is
    plot the pixel at (x, y) with brightness c (where 0 ≤ c ≤ 1)

// integer part of x
function ipart(x) is
    return floor(x)

function round(x) is
    return ipart(x + 0.5)

// fractional part of x
function fpart(x) is
    return x - floor(x)

function rfpart(x) is
    return 1 - fpart(x)

function drawLine(x0,y0,x1,y1) is
    boolean steep := abs(y1 - y0) > abs(x1 - x0)

    if steep then
        swap(x0, y0)
        swap(x1, y1)
    end if
    if x0 > x1 then
        swap(x0, x1)
        swap(y0, y1)
    end if

    dx := x1 - x0
    dy := y1 - y0

    if dx == 0.0 then
        gradient := 1.0
    else
        gradient := dy / dx
    end if

    // handle first endpoint
    xend := round(x0)
    yend := y0 + gradient * (xend - x0)
    xgap := rfpart(x0 + 0.5)
    xpxl1 := xend // this will be used in the main loop
    ypxl1 := ipart(yend)
    if steep then
        plot(ypxl1,   xpxl1, rfpart(yend) * xgap)
        plot(ypxl1+1, xpxl1,  fpart(yend) * xgap)
    else
        plot(xpxl1, ypxl1  , rfpart(yend) * xgap)
        plot(xpxl1, ypxl1+1,  fpart(yend) * xgap)
    end if
    intery := yend + gradient // first y-intersection for the main loop

    // handle second endpoint
    xend := round(x1)
    yend := y1 + gradient * (xend - x1)
    xgap := fpart(x1 + 0.5)
    xpxl2 := xend //this will be used in the main loop
    ypxl2 := ipart(yend)
    if steep then
        plot(ypxl2  , xpxl2, rfpart(yend) * xgap)
        plot(ypxl2+1, xpxl2,  fpart(yend) * xgap)
    else
        plot(xpxl2, ypxl2,  rfpart(yend) * xgap)
        plot(xpxl2, ypxl2+1, fpart(yend) * xgap)
    end if

    // main loop
    if steep then
        for x from xpxl1 + 1 to xpxl2 - 1 do
           begin
                plot(ipart(intery)  , x, rfpart(intery))
                plot(ipart(intery)+1, x,  fpart(intery))
                intery := intery + gradient
           end
    else
        for x from xpxl1 + 1 to xpxl2 - 1 do
           begin
                plot(x, ipart(intery),  rfpart(intery))
                plot(x, ipart(intery)+1, fpart(intery))
                intery := intery + gradient
           end
    end if
end function

 */


