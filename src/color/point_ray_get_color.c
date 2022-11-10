/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/10 14:18:12 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

t_point	ray_at(t_ray ray, float t)
{
	t_point	result;

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
	float		light_len;
	t_besthit	not_needed;
	t_color		color;
	double		cosangle;
	t_point		light; //temporary
	double		brightness; //temporary
	t_unit_color	dcolor;

	light = map_info.light.origin; //temporary
	brightness = (double)map_info.light.bright; //temporary
	light_ray.origin = record.hit_point;
	light_ray.dir = substract_points(light, light_ray.origin); //temporary this is actually lightray length
	light_len = sqrt((float)dot_points(light_ray.dir, light_ray.dir));
	light_ray.dir = normalize_point(light_ray.dir);
	if (hit_anything(map_info, light_ray, &not_needed, 0.01, light_len) > 0)
	{
		// calculate shadow color
		color.r = ((double)record.color.r / 255.0) / (double)M_PI * ((double)brightness + ((double)map_info.amb.color.r * map_info.amb.ratio / 255.0)) * 255.0;
		color.g = ((double)record.color.g / 255.0) / (double)M_PI * ((double)brightness + ((double)map_info.amb.color.g * map_info.amb.ratio / 255.0)) * 255.0;
		color.b = ((double)record.color.b / 255.0) / (double)M_PI * ((double)brightness + ((double)map_info.amb.color.b * map_info.amb.ratio / 255.0)) * 255.0;
		return (color);
		// return (new_color(255, 255, 255));
	}	
	cosangle = (double)dot_points(record.normal, light_ray.dir);
	if (cosangle < 0.0)
		cosangle = 0.0;
	//calculate: normalized record.color / pi * light brightness * (cosangle + ambiant)
	dcolor.r = (((double)record.color.r / 255.0) / (double)M_PI * ((double)brightness + ((double)cosangle + (double)map_info.amb.color.r * map_info.amb.ratio / 255.0)));
	dcolor.g = (((double)record.color.g / 255.0) / (double)M_PI * ((double)brightness + ((double)cosangle + (double)map_info.amb.color.g * map_info.amb.ratio / 255.0)));
	dcolor.b = (((double)record.color.b / 255.0) / (double)M_PI * ((double)brightness + ((double)cosangle + (double)map_info.amb.color.b * map_info.amb.ratio / 255.0)));
	//normalized color to color with value 0-255
	color = new_color((unsigned int)((double)dcolor.r * 255.0), (unsigned int)((double)dcolor.g * 255.0), (unsigned int)((double)dcolor.b * 255.0));
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
	// t_point		normal;
	t_besthit	record;
	int			closest_index;

	closest_index = hit_anything(map_info, ray, &record, 0.01, INFINITY);
	if (closest_index > 0)
	{
		color = calculate_shadow_shade(map_info, record);

		//real color without shading
		// color = record.color;

		//colored spheres
		// normal = normalize_point(distract_points(ray_at(ray, record.t), record.center));
		// color = new_color(0.5 * (normal.x + 1) * 255, 0.5 * (normal.y + 1) * 255, 0.5 * (normal.z + 1) * 255);
	}
	else
		color = new_color(0, 0, 0);
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
	float	x;
	float	y;
	t_point	lower_left_corner;
	t_ray	ray;
	float	scale;
	t_point	vup;
	float	viewport_width;
	float	viewport_height;
	t_point	w;
	t_point	u;
	t_point	v;

	t_point	horizontal;
	t_point	vertical;

	scale = tan((float)map_info.cam.fov * (float)(M_PI / 180.0) * 0.5); //atan? //degrees added
	viewport_width = 2.0 * scale;
	viewport_height = viewport_width / 16.0 * 9.0;

	vup = new_point(0, 1, 0);
	
	w = normalize_point(multiply_point_float(map_info.cam.dir, -1.0));
	u = normalize_point(cross_points(vup, w));
	v = cross_points(w, u);

	ray.origin = map_info.cam.origin;
	horizontal = multiply_point_float(u, viewport_width);
	vertical = multiply_point_float(v, viewport_height);

	lower_left_corner = substract_points(ray.origin, multiply_point_float(horizontal, 0.5));
	lower_left_corner = substract_points(lower_left_corner, multiply_point_float(vertical, 0.5));
	lower_left_corner = substract_points(lower_left_corner, w);

	x = (float)i / (float)(WIDTH - 1);
	y = (float)j / (float)(HEIGHT - 1);
	ray.dir = add_points(lower_left_corner, multiply_point_float(horizontal, x));
	ray.dir = add_points(ray.dir, multiply_point_float(vertical, y));
	ray.dir = substract_points(ray.dir, ray.origin);
	color = get_ray_color(map_info, ray);
	return (color);
}
