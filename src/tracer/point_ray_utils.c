/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_ray_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 12:37:15 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/11 12:38:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	calc_vertical(t_parse map_info, t_point backward)
{
	float	scale;
	float	viewport_height;
	t_point	true_up;
	t_point	left;
	t_point	vertical;

	scale = tan((float)map_info.cam.fov * (float)M_PI / 180.0 * 0.5);
	viewport_height = 2.0 * scale / 16.0 * 9.0;
	left = normalize_point(cross_points(new_point(0, 1, 0), backward));
	true_up = cross_points(backward, left);
	vertical = multiply_point_float(true_up, viewport_height);
	return (vertical);
}

t_point	calc_horizontal(t_parse map_info, t_point backward)
{
	float	scale;
	float	viewport_width;
	t_point	left;
	t_point	horizontal;

	scale = tan((float)map_info.cam.fov * (float)M_PI / 180.0 * 0.5);
	viewport_width = 2.0 * scale;
	left = normalize_point(cross_points(new_point(0, 1, 0), backward));
	horizontal = multiply_point_float(left, viewport_width);
	return (horizontal);
}

t_point	add_vertical_position(t_point dir, t_parse map_info, float j)
{
	t_point	new_dir;
	t_point	backward;
	t_point	vertical;
	float	y_orientation;

	backward = normalize_point(multiply_point_float(map_info.cam.dir, -1.0));
	vertical = calc_vertical(map_info, backward);
	y_orientation = j / (float)(HEIGHT - 1);
	new_dir = add_points(dir, multiply_point_float(vertical, y_orientation));
	return (new_dir);
}

t_point	add_horizontal_position(t_point dir, t_parse map_info, float i)
{
	t_point	new_dir;
	t_point	backward;
	t_point	horizontal;
	float	x_orientation;

	backward = normalize_point(multiply_point_float(map_info.cam.dir, -1.0));
	horizontal = calc_horizontal(map_info, backward);
	x_orientation = i / (float)(WIDTH - 1);
	new_dir = add_points(dir, multiply_point_float(horizontal, x_orientation));
	return (new_dir);
}

t_point	calc_lower_left_corner(t_parse map_info)
{
	t_point	backward;
	t_point	hor;
	t_point	ver;
	t_point	lower_left;

	backward = normalize_point(multiply_point_float(map_info.cam.dir, -1.0));
	hor = calc_horizontal(map_info, backward);
	ver = calc_vertical(map_info, backward);
	lower_left = map_info.cam.origin;
	lower_left = substract_points(lower_left, multiply_point_float(hor, 0.5));
	lower_left = substract_points(lower_left, multiply_point_float(ver, 0.5));
	lower_left = substract_points(lower_left, backward);
	return (lower_left);
}
