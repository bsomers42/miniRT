/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialias_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:20:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/** dependent on antialiasing settings (AA), make AA * AA amount of rays per
 * pixel and calculate the average color to be displayed at this pixel
 * @brief 
 * 
 * @param map_info	parsed info from .rt map
 * @param i 		x location of pixel to calculate color of
 * @param j 		y location of pixel to calculate color of
 * @return t_color 	antialiased color at point (x,y) on screen
 */
t_color	antialias_color(t_parse map_info, int i, int j)
{
	t_color	color;
	int		k;
	int		l;
	double	x;
	double	y;

	color = new_color(0, 0, 0);
	k = 0;
	while (k < AA)
	{
		l = 0;
		while (l < AA)
		{
			x = (double)i + (double)k / (double)AA;
			y = (double)j + (double)l / (double)AA;
			color = add_colors(color, point_ray_get_color(map_info, x, y));
			l++;
		}
		k++;
	}
	color = divide_color_with_double(color, AA * AA);
	return (color);
}
