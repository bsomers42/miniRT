/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/29 13:35:53 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	rotate_axis_angle(t_point vec, t_point axis, float angle)
{
	t_point	vec_orig;

	if (angle == 0)
		return (vec);
	vec_orig = vec;
	vec = multiply_point_float(vec, cos(angle));
	vec = add_points(vec, multiply_point_float((cross_points(axis, vec_orig)), sin(angle)));
	vec = add_points(vec, multiply_point_float(multiply_point_float \
		(axis, dot_points(axis, vec_orig)), (1 - cos(angle))));
	return (vec);
}

float	quadratic_form_cyl(t_cyl *cyl, t_ray rot_ray, float t_max)
{
	float	a;
	float	b;
	float	c;
	float	d;
	t_point	p;
	float	*t;
	float	t_def;

	t = malloc(3 * sizeof(float));
	a = rot_ray.dir.x * rot_ray.dir.x + rot_ray.dir.z * rot_ray.dir.z;
	b = 2 * (rot_ray.origin.x * rot_ray.dir.x + rot_ray.origin.z * \
		rot_ray.dir.z);
	c = rot_ray.origin.x * rot_ray.origin.x + rot_ray.origin.z * \
		rot_ray.origin.z - pow(cyl->radius, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
		return (-1);
	t[0] = (-b + sqrt(d)) / (2 * a);
	t[1] = (-b - sqrt(d)) / (2 * a);
	if ((t[0] < (float)T_MIN && t[1] < (float)T_MIN) || \
		(t[0] > t_max && t[1] > t_max))
		return (-1);
	if ((t[0] < t[1] && t[0] > (float)T_MIN) || t[1] < (float)T_MIN)
		t[2] = t[0];
	else
		t[2] = t[1];
	p = ray_at(rot_ray, t[2]);
	if (!(p.y > - (cyl->height / 2) && p.y < cyl->height / 2))
	{
		if (t[2] == t[0])
			t[2] = t[1];
		p = ray_at(rot_ray, t[2]);
		if (!(p.y > - (cyl->height / 2) && p.y < cyl->height / 2))
			return (-1);
	}
	t_def = t[2];
	free(t);
	return (t_def);
}

	//Note to self: don't forget to check if inside cyl!!
int	hit_tube(t_cyl *cyl, t_ray ray, float t_max, t_besthit *hit_rec)
{
	t_ray	rot_ray;
	t_point	n;
	t_point	p;
	t_point	axis;
	float	angle;
	t_point	dir_a;
	t_point	bottom_center;
	t_ray	tmp;
	float	t;
	float	x;

	angle = calc_angle(new_point(0, 1, 0), cyl);
	axis = normalize_point(cross_points(normalize_point(cyl->dir), new_point(0, 1, 0)));
	rot_ray.origin = rotate_axis_angle(substract_points(ray.origin, \
		cyl->center), axis, angle);
	rot_ray.dir = rotate_axis_angle(ray.dir, axis, angle);
	rot_ray.dir = normalize_point(rot_ray.dir);
	t = quadratic_form_cyl(cyl, rot_ray, t_max);
	if (t == -1)
		return (0);
	tmp.dir = normalize_point(cyl->dir);
	tmp.origin = cyl->center;
	p = ray_at(ray, t);
	bottom_center = ray_at(tmp, (cyl->height / 2 * -1));
	dir_a = substract_points(p, bottom_center);
	x = dot_points((dir_a), normalize_point(cyl->dir));
	n = substract_points(p, add_points((multiply_point_float \
		(normalize_point(cyl->dir), x)), bottom_center));
	hit_rec->color = cyl->color;
	hit_rec->t = t;
	hit_rec->hit_point = p;
	hit_rec->center = cyl->center;
	if (angle == 0)
		set_front_face_and_normal(rot_ray, hit_rec, n);
	else
		// set_rot_front_face_and_normal(rot)
	{
		if (dot_points(rot_ray.dir, normalize_point(n)) < 0)
		{
			hit_rec->front_face = 1;
			hit_rec->normal = rotate_axis_angle(normalize_point(n), \
				axis, angle * -1);
		}
		else
		{
			hit_rec->front_face = 0;
			hit_rec->normal = rotate_axis_angle(normalize_point(multiply_point_float \
				(normalize_point(n), -1.0)), axis, angle * -1);
		}
	}
	return (1);
}

int	hit_any_cylinder(t_parse map_info, t_ray ray, t_besthit *hit_rec, \
	float t_max)
{
	int			hit_anything;
	t_besthit	tmp_rec;
	int			i;
	t_list		*tmp;

	tmp = map_info.lst_cyl;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		if (hit_both_caps((t_cyl *)tmp->content, ray, t_max, &tmp_rec))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		if (hit_tube((t_cyl *)tmp->content, ray, t_max, &tmp_rec))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything >= 0);
}
