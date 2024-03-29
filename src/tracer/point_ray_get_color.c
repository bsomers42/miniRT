/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/14 17:49:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	ray_at(t_ray ray, double t)
{
	t_point	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

/**
 * @brief calculates the shadow of the pixel
 * 
 * @param map_info 	parsed info from .rt map
 * @param record 	the shape closest to the ray origin
 * @return t_color 	the color of the shadow
 */
static t_color	calculate_shadow(t_parse map_info, t_hit record)
{
	double	r;
	double	g;
	double	b;

	r = (((double)map_info.amb.color.r / 255.0) * map_info.amb.ratio * \
		(double)record.color.r / 255.0);
	g = (((double)map_info.amb.color.g / 255.0) * map_info.amb.ratio * \
		(double)record.color.g / 255.0);
	b = (((double)map_info.amb.color.b / 255.0) * map_info.amb.ratio * \
		(double)record.color.b / 255.0);
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
	return (new_color(r * 255.0, g * 255.0, b * 255.0));
}

/**
 * @brief calculates the shade of the pixel
 * 
 * @param map_info	parsed info from .rt map
 * @param record 	the shape closest to the ray origin
 * @param costheta 	the angle between the shape normal and the ray towards light
 * @return t_color 	the shaded color
 */
static t_color	calculate_shade(t_parse map_info, t_hit record, double costheta)
{
	double	r;
	double	g;
	double	b;

	r = (double)record.color.r * map_info.light.bright * costheta / 255.0 + \
		((double)map_info.amb.color.r / 255.0 * map_info.amb.ratio * \
		(double)record.color.r / 255.0);
	g = (double)record.color.g * map_info.light.bright * costheta / 255.0 + \
		((double)map_info.amb.color.g / 255.0 * map_info.amb.ratio * \
		(double)record.color.g / 255.0);
	b = (double)record.color.b * map_info.light.bright * costheta / 255.0 + \
		((double)map_info.amb.color.b / 255.0 * map_info.amb.ratio * \
		(double)record.color.b / 255.0);
	if (r > 1.0)
		r = 1.0;
	if (g > 1.0)
		g = 1.0;
	if (b > 1.0)
		b = 1.0;
	return (new_color(r * 255.0, g * 255.0, b * 255.0));
}

/**
 * @brief checks if this pixel is in shadow or not, calculates color of pixel
 * 
 * @param map_info 	parsed info from .rt map
 * @param record 	the shape closest to the ray origin
 * @return t_color 	the color of the pixel, shaded or in shadow
 */
static t_color	calculate_shadow_shade(t_parse map_info, t_hit record)
{
	t_ray		light_ray;
	t_hit		not_needed;
	double		costheta;
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
 * @brief point the ray in the right direction, get the color of the shape 
 * closest to the ray origin
 * 
 * @param map_info	parsed info from .rt map
 * @param i 		x location of pixel to fill
 * @param j 		y location of pixel to fill
 * @return t_color 	the found color
 */
t_color	point_ray_get_color(t_parse map_info, double i, double j)
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
