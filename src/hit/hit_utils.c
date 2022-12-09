/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/09 16:46:15 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	calc_angle(t_point upaxis, t_point dir)//t_cyl *cyl)
{
	double	angle;
	double	multip;
	double	dotproduct;

	multip = (norm(upaxis) * norm(/*cyl->*/dir));
	dotproduct = dot_points(upaxis, /*cyl->*/dir);
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

t_ray	apply_rodrigues(/*t_cyl *cyl*/ t_point dir, t_point center, t_ray ray)
{
	t_ray	rot_ray;
	t_point	axis;
	double	angle;

	angle = calc_angle(new_point(0, 1, 0), dir);
	axis = normalize_point(cross_points(normalize_point(/*cyl->*/dir), \
		new_point(0, 1, 0)));
	rot_ray.origin = rotate_axis_angle(substract_points(ray.origin, \
		/*cyl->*/center), axis, angle);
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
