/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialias_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:20:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 11:55:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief dependent on antialiasing settings (AA), make x amount of rays per 
 * pixel and calculate the average color to be displayed on this pixel;
 * 
 * @param map_info 
 * @param i 		x location of pixel to calculate color
 * @param j 		y location of pixel to calculate color
 * @return t_color 
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
