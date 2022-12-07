/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/07 16:18:40 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	calc_angle(t_point upaxis, t_cyl *cyl)
{
	float	angle;
	float	multip;
	float	dotproduct;

	multip = (norm(upaxis) * norm(cyl->dir));
	dotproduct = dot_points(upaxis, cyl->dir);
	angle = acos(dotproduct / multip);
	return (angle);
}

t_point	rotate_axis_angle(t_point vec, t_point axis, float angle)
{
	t_point	vec_orig;

	if (angle == 0)
		return (vec);
	vec_orig = vec;
	vec = multiply_point_float(vec, cos(angle));
	vec = add_points(vec, multiply_point_float((cross_points(axis, vec_orig)), \
		sin(angle)));
	vec = add_points(vec, multiply_point_float(multiply_point_float \
		(axis, dot_points(axis, vec_orig)), (1 - cos(angle))));
	return (vec);
}

t_ray	apply_rodrigues(t_cyl *cyl, t_ray ray)
{
	t_ray	rot_ray;
	t_point	axis;
	float	angle;

	angle = calc_angle(new_point(0, 1, 0), cyl);
	axis = normalize_point(cross_points(normalize_point(cyl->dir), \
		new_point(0, 1, 0)));
	rot_ray.origin = rotate_axis_angle(substract_points(ray.origin, \
		cyl->center), axis, angle);
	rot_ray.dir = normalize_point(rotate_axis_angle(ray.dir, axis, angle));
	return (rot_ray);
}

void	set_normal(t_ray ray, t_hit *hit_rec, t_point n)
{
	if (dot_points(ray.dir, n) < 0)
		hit_rec->normal = n;
	else
		hit_rec->normal = multiply_point_float(n, -1.0);
}

float	norm(t_point vec)
{
	float	res;

	res = (float)powf(vec.x, 2);
	res += (float)powf(vec.y, 2);
	res += (float)powf(vec.z, 2);
	return ((float)sqrtf(res)); //jma sqrt of sqrtf?
}
