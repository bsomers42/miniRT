/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialias_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:20:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/20 14:23:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	antialias_color(t_list *spheres, t_ray ray, int i, int j)
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
			color = add_colors(color, decide_color(spheres, ray, x, y));
			l++;
		}
		k++;
	}
	color = devide_color_with_float(color, AA * AA);
	return (color);
}
