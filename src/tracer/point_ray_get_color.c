/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/28 17:34:34 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h> //remove at end

t_point	ray_at(t_ray ray, float t)
{
	t_point	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

t_color	calculate_shadow(t_parse map_info, t_hit record)
{
	float	r;
	float	g;
	float	b;

	r = (((float)map_info.amb.color.r / 255.0) * map_info.amb.ratio * \
		(float)record.color.r / 255.0);
	g = (((float)map_info.amb.color.g / 255.0) * map_info.amb.ratio * \
		(float)record.color.g / 255.0);
	b = (((float)map_info.amb.color.b / 255.0) * map_info.amb.ratio * \
		(float)record.color.b / 255.0);
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
	return (new_color(r * 255.0, g * 255.0, b * 255.0));
}

/**
 * @brief calculates the shade of the pixel: 
 * 
 * @param map_info 
 * @param record 
 * @param costheta 
 * @return t_color 
 */
t_color	calculate_shade(t_parse map_info, t_hit record, float costheta)
{
	float	r;
	float	g;
	float	b;

	r = (float)record.color.r * map_info.light.bright * costheta / 255.0 + \
		((float)map_info.amb.color.r / 255.0 * map_info.amb.ratio * \
		(float)record.color.r / 255.0);
	g = (float)record.color.g * map_info.light.bright * costheta / 255.0 + \
		((float)map_info.amb.color.g / 255.0 * map_info.amb.ratio * \
		(float)record.color.g / 255.0);
	b = (float)record.color.b * map_info.light.bright * costheta / 255.0 + \
		((float)map_info.amb.color.b / 255.0 * map_info.amb.ratio * \
		(float)record.color.b / 255.0);
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
	return (new_color(r * 255.0, g * 255.0, b * 255.0));
}

/**
 * @brief If this pixel is in the shadow, calculate the ambient light at this
 *  pixel. If not in the shadow, calculate the combination of ambient and 
 * normal light coming together at this pixel.
 * 
 * @param map_info 	parsed info from .rt map
 * @param record 	information on the object closest to the ray origin
 * @return t_color 	the shaded color
 */
t_color	calculate_shadow_shade(t_parse map_info, t_hit record)
{
	t_ray		light_ray;
	t_hit		not_needed;
	float		costheta;
	t_point		light_line;

	light_ray.origin = record.hit_point;
	light_line = substract_points(map_info.light.origin, light_ray.origin);
	not_needed.t = norm(light_line);
	light_ray.dir = normalize_point(light_line);
	if (hit_anything(map_info, light_ray, &not_needed) > 0)
	{
		return (calculate_shadow(map_info, record));
	}
	costheta = dot_points(record.normal, light_ray.dir);
	if (costheta < 0.0)
		costheta = 0.0;
	return (calculate_shade(map_info, record, costheta));
}

/**
 * @brief point the ray in the right direction, get the color of the object 
 * intersecting ray.dir closest to ray.origin
 * 
 * @param map_info	parsed info from .rt map
 * @param i 		x location of pixel to calculate color of
 * @param j 		y location of pixel to calculate color of
 * @return t_color 	the found color  
 */
t_color	point_ray_get_color(t_parse map_info, float i, float j)
{
	t_ray		ray;
	t_color		color;
	t_hit		record;
	int			closest_index;

	ray.origin = map_info.cam.origin;
	ray.dir = map_info.cam.llc;
	ray.dir = add_horizontal_position(ray.dir, map_info, i);
	ray.dir = add_vertical_position(ray.dir, map_info, j);
	ray.dir = substract_points(ray.dir, ray.origin);
	ray.dir = normalize_point(ray.dir);
	record.t = INFINITY;
	closest_index = hit_anything(map_info, ray, &record);
	if (closest_index > 0)
		color = calculate_shadow_shade(map_info, record);
	else
		color = new_color(0, 0, 0);
	return (color);
}
