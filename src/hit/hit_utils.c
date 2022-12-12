/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/12 12:11:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

double	calc_angle(t_point upaxis, t_point dir)
{
	double	angle;
	double	multip;
	double	dotproduct;

	multip = (norm(upaxis) * norm(dir));
	dotproduct = dot_points(upaxis, dir);
	angle = acos(dotproduct / multip);
	return (angle);
}

t_point	rotate_axis_angle(t_point vec, t_point axis, double angle)
{
	t_point	vec_orig;

	if (angle == 0)
		return (vec);
	vec_orig = vec;
	vec = multiply_point_double(vec, cos(angle));
	vec = add_points(vec, multiply_point_double((cross_points(axis, vec_orig)), \
		sin(angle)));
	vec = add_points(vec, multiply_point_double(multiply_point_double \
		(axis, dot_points(axis, vec_orig)), (1 - cos(angle))));
	return (vec);
}

t_ray	apply_rodrigues(t_point dir, t_point center, t_ray ray)
{
	t_ray	rot_ray;
	t_point	axis;
	double	angle;

	angle = calc_angle(new_point(0, 1, 0), dir);
	if (dir.y < 0 && dir.x == 0 && dir.z == 0)
		axis = normalize_point(cross_points(normalize_point(dir), \
		new_point(0, 0, 1)));
	else
		axis = normalize_point(cross_points(normalize_point(dir), \
		new_point(0, 1, 0)));
	rot_ray.origin = rotate_axis_angle(substract_points(ray.origin, \
		center), axis, angle);
	rot_ray.dir = normalize_point(rotate_axis_angle(ray.dir, axis, angle));
	return (rot_ray);
}

void	set_normal(t_ray ray, t_hit *hit_rec, t_point n)
{
	if (dot_points(ray.dir, n) < 0)
		hit_rec->normal = n;
	else
		hit_rec->normal = multiply_point_double(n, -1.0);
}

double	norm(t_point vec)
{
	double	res;

	res = (double)powf(vec.x, 2);
	res += (double)powf(vec.y, 2);
	res += (double)powf(vec.z, 2);
	return ((double)sqrt(res));
}
