/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_get_color.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/02 13:51:45 by jaberkro      ########   odam.nl         */
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
	t_besthit	not_needed;
	t_color		color;
	float		angle;
	t_point		light; //temporary
	float		brightness; //temporary

	light = map_info.light.origin;//new_point(1, 2, 1); //temporary
	brightness = map_info.light.bright; //1.0; //temporary
	light_ray.origin = record.hit_point;
	light_ray.dir = substract_points(light, light_ray.origin); //temporary
	// light_ray.dir = distract_points(map_info.light->origin, light_ray.origin); above should become this
	light_ray.dir = normalize_point(light_ray.dir);
	if (hit_anything(map_info, light_ray, &not_needed, 0.001, sqrt(dot_points(light_ray.dir, light_ray.dir))) >= 0)
		return (new_color(0, 0, 0));
	angle = dot_points(record.normal, light_ray.dir);
	if (angle < 0.0)
		angle = 0.0;
	color = multiply_color_float(record.color, angle * brightness); //test but seems to work
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

	closest_index = hit_anything(map_info, ray, &record, 0, INFINITY);
	if (closest_index >= 0)
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
	float	s;
	float	t;
	t_point	lower_left_corner;
	t_ray	ray;
	float 	hfov;
	float	theta;
	float	h;
	t_point	lookfrom;
	t_point	lookat;
	t_point	vup;
	unsigned int	viewport_width;
	unsigned int	viewport_height;
	t_point	w;
	t_point	u;
	t_point	v;

	t_point	horizontal;
	t_point	vertical;

	hfov = map_info.cam.fov;//105.0;
	theta = hfov * (float)(M_PI / 180.0);
	h = tan((float)theta / 2); //atan?
	viewport_height = 2.0;// * h;
	viewport_width = 16.0 / 9.0 * (float)viewport_height * h;

	lookfrom = map_info.cam.origin;//new_point(-2, 2, 1);//map_info.cam.origin;//new_point(map_info.cam.x, map_info.cam.y, map_info.cam.z);//new_point(-2, 2, 1); // temporary
	lookat = map_info.cam.dir;//new_point(0, 0, 1);//ray_at(map_info.cam.dir, FOCAL_LENGTH); //map_info.cam.dir;// temporary
	vup = new_point(0, 1, 0);

	w = normalize_point(substract_points(lookfrom, lookat));// map_info.cam.dir; //
	u = normalize_point(cross_points(vup, w));
	v = cross_points(w, u);

	horizontal = multiply_point_float(u, viewport_width);
	vertical = multiply_point_float(v, viewport_height);

	ray.origin = lookfrom;
	// ray.dir.x = 0.0; // temporary
	// ray.dir.y = 0.0; // temporary
	// ray.dir.z = 0.0; // temporary
	// ray.origin = map_info.cam->origin; // create the ray
	lower_left_corner = substract_points(ray.origin, multiply_point_float(horizontal, 0.5));
	lower_left_corner = substract_points(lower_left_corner, multiply_point_float(vertical, 0.5));
	lower_left_corner = substract_points(lower_left_corner, w);
	s = i / (float)(WIDTH - 1);
	t = j / (float)(HEIGHT - 1);
	ray.dir = add_points(lower_left_corner, multiply_point_float(horizontal, s));
	ray.dir = add_points(ray.dir, multiply_point_float(vertical, t));
	ray.dir = substract_points(ray.dir, ray.origin);
	color = get_ray_color(map_info, ray);
	return (color);
}
