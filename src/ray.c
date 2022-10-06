/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:00:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 15:25:19 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen

t_color	ray_color(t_ray ray)
{
	t_coord	unit_direction;
	float	t;
	t_color	white;
	t_color	blue;
	t_color	color;

	(void)ray;
	white = new_color(1.0, 1.0, 1.0);
	blue = new_color(0.5, 0.7, 1.0);
	unit_direction = unit_vector_coord(ray.dir);
	t = 0.5 * (unit_direction.y + 1.0);
	// printf("t:%f\n", t);
	// color = multiply_color_float(white, 1.0 - t);
	printf("unit_dir x:%f, y:%f, z:%f\n", unit_direction.x, unit_direction.y, unit_direction.z);
	// color = add_colors(multiply_color_float(white, 1.0 - t), multiply_color_float(blue, t));
	color.r = 255 * ((1.0 - t) * 1.0 + 0.5 * t);
	color.g = 255 * ((1.0 - t) * 1.0 + 0.7 * t);
	color.b = 255 * ((1.0 - t) * 1.0 + 1.0 * t);
	return (color);
}

t_coord	ray_at(t_ray ray, float t)
{
	t_coord	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}
