/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 12:00:58 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

t_coord	ray_at(t_ray ray, float t)
{
	t_coord	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

/**
 * @brief calculate if this pixel can see the light or is in the shadow. In the
 * case of shadow, color is black. Else, the color will be a gradient between
 * black and full color of the shape.
 * 
 * @param map_info 
 * @param record 	closest shape to the camera, hit by the ray
 * @return t_color 
 */
t_color	calculate_shadow_shade(t_parse map_info, t_besthit record)
{
	t_ray		light_ray;
	t_besthit	not_needed;
	t_color		color;
	t_coord		light; //temporary
	float		brightness; //temporary
	float		angle;

	light.x = 0.0; //temporary
	light.y = 1.0; //temporary
	light.z = 0.0; //temporary
	brightness = 1.0; //temporary
	light_ray.origin = record.hit_point;
	light_ray.dir = substract_points(light, light_ray.origin); //temporary
	// light_ray.dir = distract_points(map_info.light->origin, light_ray.origin); above should become this
	light_ray.dir = unit_vector_coord(light_ray.dir);
	if (hit_anything(map_info, light_ray, &not_needed, 0.001, sqrt(dot_points(light_ray.dir, light_ray.dir))) >= 0)
		return (new_color(0, 0, 0));
	light_ray.dir = substract_points(light_ray.origin, light); // temporary
	// light_ray.dir = distract_points(light_ray.origin, map_info.light->origin); // above should become this, but not sure about this line yet
	light_ray.dir = unit_vector_coord(light_ray.dir);
	light_ray.dir = multiply_point_float(light_ray.dir, -1.0);
	angle = dot_points(record.normal, light_ray.dir);
	if (angle < 0)
		angle = 0;
	color = multiply_color_float(record.color, (float)angle * (float)brightness); //test
	return (color);
}

/**
 * @brief Get the color is this ray. If you hit nothing, color is black. Else,
 * the color is the shaded version of the color of the shape closest to you. 
 * 
 * @param map_info 
 * @param ray 
 * @return t_color 
 */
static t_color	get_ray_color(t_parse map_info, t_ray ray)
{
	t_color		color;
	// t_coord		normal;
	t_besthit	record;
	int			closest_index;

	closest_index = hit_anything(map_info, ray, &record, 0, INFINITY);
	if (closest_index >= 0)
	{
		color = calculate_shadow_shade(map_info, record);

		//real color without shading
		// color = record.color;

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

/**
 * @brief point the ray in the right direction
 * 
 * @param map_info 
 * @param i 
 * @param j 
 * @return t_color 
 */
t_color	point_ray_get_color(t_parse map_info, float i, float j) // point_ray
{
	t_color	color;
	float	u;
	float	v;
	t_coord	lower_left_corner;
	t_ray	ray;
	// float 	vfov; // VERTICAL field-of-view -> should become horiontal at some point
	// float	theta;
	// float	h;

	// theta = 
	ray.origin.x = 0.0; // this should be removed
	ray.origin.y = 0.0; // this should be removed
	ray.origin.z = 0.0; // this should be removed
	ray.dir.x = 1.0; // this should be removed
	ray.dir.y = 0.0; // this should be removed
	ray.dir.z = 0.0; // this should be removed
	// ray.origin = map_info.cam->origin; // create the ray
	lower_left_corner.x = ray.origin.x - VIEWPORT_WIDTH / 2;
	lower_left_corner.y = ray.origin.y - VIEWPORT_HEIGHT / 2;
	lower_left_corner.z = ray.origin.z - FOCAL_LENGTH;
	u = i / (WIDTH - 1);
	v = j / (HEIGHT - 1);
	ray.dir.x = lower_left_corner.x + u * VIEWPORT_WIDTH - ray.origin.x;
	ray.dir.y = lower_left_corner.y + v * VIEWPORT_HEIGHT - ray.origin.y;
	ray.dir.z = lower_left_corner.z - ray.origin.z;
	color = get_ray_color(map_info, ray);
	return (color);
}
