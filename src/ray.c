/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:00:24 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/07 13:07:39 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen

t_coord	ray_at(t_ray ray, float t)
{
	t_coord	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

t_color	ray_color(t_sphere *spheres, t_ray ray)
{
	t_coord	unit_direction;
	float	t;
	t_color	white;
	t_color	blue;
	t_color	color;
	t_coord point;
	t_coord normal;
	t_besthit record;
	int		closest_index;

	point.x = 0;
	point.y = 0;
	point.z = -1;
	t = 0.0;
	closest_index = hit_anything(spheres, ray, &record);
	if (closest_index >= 0)
	{
		normal = unit_vector_coord(distract_points(ray_at(ray, record.t), spheres[closest_index].center));
		color = new_color(0.5 * (normal.x + 1) * 255, 0.5 * (normal.y + 1) * 255, 0.5 * (normal.z + 1) * 255);
		// normal = unit_vector_coord(distract_points(ray_at(ray, t), point));
	}
	else
	{
		white = new_color(1.0, 1.0, 1.0);
		blue = new_color(0.5, 0.7, 1.0);
		unit_direction = unit_vector_coord(ray.dir);
		t = 0.5 * (unit_direction.y + 1.0);
		// color = multiply_color_float(add_colors(multiply_color_float(white, 1.0 - t), multiply_color_float(blue, t)), 255);
		color.r = 255 * ((1.0 - t) * 1.0 + 0.5 * t);
		color.g = 255 * ((1.0 - t) * 1.0 + 0.7 * t);
		color.b = 255 * ((1.0 - t) * 1.0 + 1.0 * t);
	}
	return (color);
}

// unsigned int	find_colour(t_sphere *spheres, t_ray ray, int samples_per_pixel)
// {
// 	t_coord			normal;
// 	unsigned int	colour;
// 	t_coord			unit_dir;
// 	int				closest_index;
// 	t_besthit		hit_rec;

// 	closest_index = hit_anything(spheres, ray, &hit_rec);
// 	if (closest_index >= 0)
// 	{
// 		normal = unit_vector(minus(at(ray, hit_rec.t), spheres[closest_index].center));
// 		colour = calculate_colour(0.5 * (normal.x + 1), 0.5 * (normal.y + 1), 0.5 * (normal.z + 1), samples_per_pixel);
// 	}
// 	else
// 	{
// 		unit_dir = (unit_vector(ray.dir));
// 		hit_rec.t = 0.5 * (unit_dir.y + 1.0);
// 		colour =  calculate_colour(1.0 * (1.0 - hit_rec.t), 1.0 * (1.0 - hit_rec.t), 1.0 * (1.0 - hit_rec.t), samples_per_pixel) + calculate_colour(0.5 * hit_rec.t, 0.7 * hit_rec.t, 1.0 * hit_rec.t, samples_per_pixel);
// 	}
// 	return (colour);
// }

