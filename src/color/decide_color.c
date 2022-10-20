/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decide_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/20 15:27:24 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	ray_at(t_ray ray, float t)
{
	t_coord	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

int	calculate_shadow(t_list *spheres, t_besthit record)
{
	t_coord		light;
	t_ray		light_ray;
	t_besthit	not_needed;

	light.x = 1.0;
	light.y = 1.0;
	light.z = -0.1;
	light_ray.origin = record.hit_point;
	light_ray.dir = distract_points(light, light_ray.origin);
	if (hit_anything(spheres, light_ray, &not_needed, 0.1) >= 0)
		return (1);
	return (0);
}

static t_color	ray_color(t_list *spheres, t_ray ray)
{
	t_color		color;
	// t_coord		normal;
	t_besthit	record;
	int			closest_index;
	
	closest_index = hit_anything(spheres, ray, &record, 0);
	if (closest_index >= 0)
	{
		if (calculate_shadow(spheres, record) == 1)
			return (new_color(64, 64, 64)); // final shadow color should be black
		// //actual color
		color = record.color;
		//als geen schaduw dan shading berekenen en terug sturen
		// record.normal;
		
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
