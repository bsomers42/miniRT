/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialias_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:20:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/11 14:10:56 by jaberkro      ########   odam.nl         */
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
	float	x;
	float	y;

	color = new_color(0, 0, 0);
	k = 0;
	while (k < AA)
	{
		l = 0;
		while (l < AA)
		{
			x = (float)i + (float)k / (float)AA;
			y = (float)j + (float)l / (float)AA;
			color = add_colors(color, point_ray_get_color(map_info, x, y));
			l++;
		}
		k++;
	}
	color = divide_color_with_float(color, AA * AA);
	return (color);
}
