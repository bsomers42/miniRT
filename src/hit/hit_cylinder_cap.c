/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder_cap.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:38:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/18 17:46:55 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_point	calc_cap_center(t_cyl *cyl, int side)
{
	t_point	cap_center;
	t_ray	tmp;

	tmp.dir = normalize_point(cyl->dir);
	tmp.origin = cyl->center;
	if (side == 0)
		cap_center = ray_at(tmp, (cyl->height / 2));
	if (side == 1)
		cap_center = ray_at(tmp, (cyl->height / 2 * -1));
	return (cap_center);
}

int	intersect_circle(t_cyl *cyl, t_ray ray, float t, t_point cap_center)
{
	t_point	p;
	t_point	v;
	float	d;

	p = ray_at(ray, t);
	v = substract_points(p, cap_center);
	d = dot_points(v, v);
	return (sqrtf(d) <= cyl->radius);
}

int	hit_cap(t_cyl *cyl, t_ray ray, float t_max, t_hit *hit_rec, \
	t_point cap_center)
{
	float	t;
	float	denom;
	t_point	n;
	t_point	polo;

	n = normalize_point(cyl->dir);
	denom = dot_points(n, ray.dir);
	if (fabs(denom) > 0)
	{
		polo = substract_points(cap_center, ray.origin);
		t = (float)dot_points(polo, n) / (float)denom;
		if (t >= T_MIN && t < t_max)
		{
			if (intersect_circle(cyl, ray, t, cap_center))
			{
				hit_rec->t = t;
				hit_rec->hit_point = ray_at(ray, hit_rec->t);
				hit_rec->color = cyl->color;
				hit_rec->center = cyl->center;
				set_front_face_and_normal(ray, hit_rec, n);
				return (1);
			}
		}
	}
	return (0);
}

int	hit_both_caps(t_cyl *cyl, t_ray ray, float t_max, t_hit *tmp_rec)
{
	t_point		tmp_center;

	tmp_center = calc_cap_center(cyl, 0);
	if (hit_cap(cyl, ray, t_max, tmp_rec, tmp_center))
		return (1);
	tmp_center = calc_cap_center(cyl, 1);
	if (hit_cap(cyl, ray, t_max, tmp_rec, tmp_center))
		return (1);
	return (0);
}
