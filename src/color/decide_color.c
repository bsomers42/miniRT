/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decide_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/20 18:53:13 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

t_color	clamp_color(t_color color, unsigned int min, unsigned int max)
{
	t_color	new_color;

	if (color.r < min)
		new_color.r = min;
	if (color.g < min)
		new_color.g = min;
	if (color.b < min)
		new_color.b = min;
	if (color.r > max)
		new_color.r = max;
	if (color.g > max)
		new_color.g = max;
	if (color.b > max)
		new_color.b = max;
	return (new_color);
}

t_coord	ray_at(t_ray ray, float t)
{
	t_coord	result;

	result.x = ray.origin.x + t * ray.dir.x;
	result.y = ray.origin.y + t * ray.dir.y;
	result.z = ray.origin.z + t * ray.dir.z;
	return (result);
}

t_color	calculate_shadow_shade(t_list *spheres, t_besthit record)
{
	t_ray		light_ray;
	t_besthit	not_needed;
	t_color		color;
	t_coord		light;
	float		brightness;
	t_color		test_print;
	float angle;

	light.x = 1.0;
	light.y = 1.0;
	light.z = -0.1;
	brightness = 1.0;
	light_ray.origin = record.hit_point;
	light_ray.dir = distract_points(light, light_ray.origin);
	light_ray.dir = unit_vector_coord(light_ray.dir);
	if (hit_anything(spheres, light_ray, &not_needed, 0.001, sqrt(dot_points(light_ray.dir, light_ray.dir))) >= 0)
		return (new_color(64, 64, 64));
	light_ray.dir = distract_points(light_ray.origin, light); // twijfel
	light_ray.dir = unit_vector_coord(light_ray.dir); //twijfel
	light_ray.dir = multiply_point_float(light_ray.dir, -1.0); //twijfel
	angle = dot_points(record.normal, light_ray.dir); // lijkt niet het goede resultaat te hebben
	if (angle > 0)
	{
		printf("angle:%f\n", angle);
		test_print = multiply_color_float(new_color(255, 255, 255), 0.18 / M_PI * brightness * angle);
	// 	// color = multiply_color_float(new_color(255, 255, 255), 0.18 / M_PI * brightness * fmax(0.0, dot_points(record.normal, light_ray.dir)));
		test_print = clamp_color(test_print, 0, 255);
		color = multiply_colors(record.color, test_print);
		color = clamp_color(color, 0, 255);
		// color = record.color; // als je dit uitcomment komt er random shit
	}
	else
		color = new_color(64, 64, 64);
	// color = multiply_color_float(record.color, test_print * 255);
	// color = multiply_color_float(new_color(255, 255, 255), 0.18 / M_PI * brightness * fmax(0.0, dot_points(record.normal, light_ray.dir)));
	return (color);
}

static t_color	ray_color(t_list *spheres, t_ray ray)
{
	t_color		color;
	// t_coord		normal;
	t_besthit	record;
	int			closest_index;

	closest_index = hit_anything(spheres, ray, &record, 0, INFINITY);
	if (closest_index >= 0)
	{
		// if (calculate_shadow_shade(light, spheres, record) == 1)
		// 	return (new_color(64, 64, 64)); // final shadow color should be black
		//actual color
		color = calculate_shadow_shade(spheres, record); //record.color;
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
