/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/11 14:32:06 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	ray_at(t_ray ray, float t)
{
	t_point	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
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
t_color	calculate_shadow_shade(t_parse map_info, t_besthit record)
{
	t_ray		light_ray;
	float		light_len;
	t_besthit	not_needed;
	t_color		color;
	double		cosangle;

	light_ray.origin = record.hit_point;
	light_ray.dir = substract_points(map_info.light.origin, light_ray.origin); //temporary this is actually lightray length
	light_len = sqrt((float)dot_points(light_ray.dir, light_ray.dir));
	light_ray.dir = normalize_point(light_ray.dir);
	if (hit_anything(map_info, light_ray, &not_needed, 0.01, light_len) > 0) // or inside of shape?
	{
		color.r = ((float)record.color.r / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((float)map_info.amb.color.r * map_info.amb.ratio / 255.0)) * 255.0;
		color.g = ((float)record.color.g / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((float)map_info.amb.color.g * map_info.amb.ratio / 255.0)) * 255.0;
		color.b = ((float)record.color.b / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((float)map_info.amb.color.b * map_info.amb.ratio / 255.0)) * 255.0;
		return (color);
	}	
	cosangle = (float)dot_points(record.normal, light_ray.dir);
	if (cosangle < 0.0)
		cosangle = 0.0;
	color.r = (((float)record.color.r / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((float)cosangle + (float)map_info.amb.color.r * map_info.amb.ratio / 255.0))) * 255.0;
	color.g = (((float)record.color.g / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((float)cosangle + (float)map_info.amb.color.g * map_info.amb.ratio / 255.0))) * 255.0;
	color.b = (((float)record.color.b / 255.0) / (float)M_PI * ((float)(float)map_info.light.bright + ((double)cosangle + (double)map_info.amb.color.b * map_info.amb.ratio / 255.0))) * 255.0;
	return (color);
}

/**
 * @brief Get the color is this ray. If you hit nothing, color is black. Else,
 * the color is the shaded version of the color of the shape closest to you. 
 * 
 * @param map_info parsed info from .rt map
 * @param ray 
 * @return t_color 
 */
t_color	get_ray_color(t_parse map_info, t_ray ray)
{
	t_color		color;
	t_besthit	record;
	int			closest_index;

	closest_index = hit_anything(map_info, ray, &record, 0.01, INFINITY);
	if (closest_index > 0)
	{
		color = calculate_shadow_shade(map_info, record);
		// color = record.color;
	}
	else
		color = new_color(0, 0, 0);
	return (color);
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
	t_ray	ray;
	t_color	color;

	ray.origin = map_info.cam.origin;
	ray.dir = calc_lower_left_corner(map_info);
	ray.dir = add_horizontal_position(ray.dir, map_info, i);
	ray.dir = add_vertical_position(ray.dir, map_info, j);
	ray.dir = substract_points(ray.dir, ray.origin);
	color = get_ray_color(map_info, ray);
	return (color);
}
