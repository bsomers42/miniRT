/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decide_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/19 16:05:27 by jaberkro      ########   odam.nl         */
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

static t_color	ray_color(t_list *spheres, t_ray ray)
{
	t_color		color;
	// t_coord		normal;
	t_besthit	record;
	int			closest_index;

	closest_index = hit_anything(spheres, ray, &record);
	if (closest_index >= 0)
	{
		// printf("sphere center: %f, %f, %f\n", sphere->center.x, sphere->center.y, sphere->center.x);
		// //actual color
		color = record.color;
		//colored spheres
		// normal = unit_vector_coord(distract_points(ray_at(ray, record.t), record.center));
		// color = new_color(0.5 * (normal.x + 1) * 255, 0.5 * (normal.y + 1) * 255, 0.5 * (normal.z + 1) * 255);
	}
	else
	{
		color = new_color(0, 0, 0);
	}
	return (color);
}

t_color	decide_color(t_list *spheres, t_ray ray, float i, float j)
{
	t_color	color;
	float	u;
	float	v;
	t_coord	lower_left_corner;

	lower_left_corner.x = ray.origin.x - VIEWPORT_WIDTH / 2;
	lower_left_corner.y = ray.origin.y - VIEWPORT_HEIGHT / 2;
	lower_left_corner.z = ray.origin.z - FOCAL_LENGTH;
	u = i / (WIDTH - 1);
	v = j / (HEIGHT - 1);
	ray.dir.x = lower_left_corner.x + u * VIEWPORT_WIDTH - ray.origin.x;
	ray.dir.y = lower_left_corner.y + v * VIEWPORT_HEIGHT - ray.origin.y;
	ray.dir.z = lower_left_corner.z - ray.origin.z;
	color = ray_color(spheres, ray);
	return (color);
}
