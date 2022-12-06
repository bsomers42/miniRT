/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 12:37:15 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/06 21:34:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	calc_vertical(t_parse map_info)
{
	float	scale;
	float	viewport_height;
	t_point	true_up;
	t_point	left;
	t_point	vertical;

	scale = tan((float)map_info.cam.fov * (float)M_PI / 180.0 * 0.5);
	viewport_height = 2.0 * scale / 16.0 * 9.0;
	if (map_info.cam.back.x == 0 && (map_info.cam.back.y == 1 || \
		map_info.cam.back.y == -1) && map_info.cam.back.z == 0)
		left = new_point(-1, 0, 0);
	else
		left = normalize_point(cross_points(new_point(0, 1, 0), \
		map_info.cam.back));
	true_up = cross_points(map_info.cam.back, left);
	vertical = multiply_point_float(true_up, viewport_height);
	return (vertical);
}

t_point	calc_horizontal(t_parse map_info)
{
	float	scale;
	float	viewport_width;
	t_point	left;
	t_point	horizontal;

	scale = tan((float)map_info.cam.fov * (float)M_PI / 180.0 * 0.5);
	viewport_width = 2.0 * scale;
	if (map_info.cam.back.x == 0 && (map_info.cam.back.y == 1 || \
		map_info.cam.back.y == -1) && map_info.cam.back.z == 0)
		left = new_point(-1, 0, 0);
	else
		left = normalize_point(cross_points(new_point(0, 1, 0), \
		map_info.cam.back));
	horizontal = multiply_point_float(left, viewport_width);
	return (horizontal);
}

t_point	add_vertical_position(t_point dir, t_parse map_info, float j)
{
	t_point	new_dir;
	t_point	vertical;
	float	y_orientation;

	vertical = map_info.cam.vertical;
	y_orientation = j / (float)(HEIGHT - 1);
	new_dir = add_points(dir, multiply_point_float(vertical, y_orientation));
	return (new_dir);
}

t_point	add_horizontal_position(t_point dir, t_parse map_info, float i)
{
	t_point	new_dir;
	t_point	horizontal;
	float	x_orientation;

	horizontal = map_info.cam.horizontal;
	x_orientation = i / (float)(WIDTH - 1);
	new_dir = add_points(dir, multiply_point_float(horizontal, x_orientation));
	return (new_dir);
}

t_point	calculate_lower_left_corner(t_parse map_info)
{
	t_point	back;
	t_point	hor;
	t_point	ver;
	t_point	lower_left;

	hor = map_info.cam.horizontal;
	ver = map_info.cam.vertical;
	back = map_info.cam.back;
	lower_left = map_info.cam.origin;
	lower_left = substract_points(lower_left, multiply_point_float(hor, 0.5));
	lower_left = substract_points(lower_left, multiply_point_float(ver, 0.5));
	lower_left = substract_points(lower_left, back);
	return (lower_left);
}
