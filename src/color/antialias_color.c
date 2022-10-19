/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   antialias_color.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 17:20:40 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/19 14:58:50 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen

t_color	antialias_color(t_list *spheres, t_ray ray, int x, int y)
{
	t_color	color;
	int		k;
	int		l;

	color = new_color(0, 0, 0);
	k = 0;
	while (k < AA)
	{
		l = 0;
		while (l < AA)
		{
			color = add_colors(color, decide_color(spheres, ray, (float)(x) + (float)(k) / (float)(AA), (float)(y) + (float)l / (float)AA));
			l++;
		}
		k++;
	}
	color = devide_color_with_float(color, AA * AA);
	return (color);
}
