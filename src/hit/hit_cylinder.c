/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/16 12:56:47 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h> ///wegggg

t_vector	multiply_vec(t_vector first, t_vector second)
{
	t_vector	result;

	result.x = first.x * second.x;
	result.y = first.y * second.y;
	result.z = first.z * second.z;
	return (result);
}

t_point	calc_cap_center(t_cyl *cyl, int side)
{
	t_point	cap_center;
	t_ray	tmp;

	tmp.dir = cyl->dir;
	tmp.origin = cyl->center;

	if (side == 0)
	{
		cap_center = ray_at(tmp, (cyl->height / 2));
	}	
	if (side == 1)
	{
		cap_center = ray_at(tmp, (cyl->height /2 * -1 ));
	}
	return (cap_center);
}

int	intersect_circle(t_cyl *cyl, t_ray ray, float t, t_point cap_center)
{
	float	radius;
	t_point	p;
	t_point	v;
	float	d;

	radius = cyl->diam / 2;
	p = ray_at(ray, t);
	v = substract_points(p, cap_center);
	d = dot_points(v, v);
	return (sqrtf(d) <= radius);
}

int	hit_cap(t_cyl *cyl, t_ray ray, float t_min, float t_max, t_besthit *hit_rec, t_point cap_center)
{
	float	t;
	float	denom;
	t_point	n;
	t_point	polo;

	n = normalize_point(cyl->dir);
	denom = dot_points(n, ray.dir);
	if (fabs(denom) > t_min) //Jorien wilt hier suuuuuuupergraag een 0 
	{
		polo = substract_points(cap_center, ray.origin);
		t = (float)dot_points(polo, n) / (float)denom;
		if (t >= t_min && t < t_max)
		{
			if (intersect_circle(cyl, ray, t, cap_center))
			{
				hit_rec->t = t;
				hit_rec->hit_point = ray_at(ray, hit_rec->t);
				hit_rec->color = new_color(255,0,255);//cyl->color;
				hit_rec->center = cyl->center;
				if (dot_points(ray.dir, n) < 0)
				{
					hit_rec->front_face = 1;
					hit_rec->normal = n;
				}
				else
				{
					hit_rec->front_face = 0;
					hit_rec->normal = multiply_point_float(n, -1.0);
				}
				return (1);
			}
		}
	}
	return (0);
}

float	norm(t_point vec)
{
	float	res = 0;
	res += pow(vec.x, 2);
	res += pow(vec.y, 2);
	res += pow(vec.z, 2);
	return (sqrt(res));
}

float	calc_angle(t_point upaxis, t_cyl *cyl)
{
	float	angle;
	float	multip;
	float	dotproduct;

	multip = fabs((norm(upaxis) * norm(cyl->dir)));
	dotproduct = dot_points(upaxis, cyl->dir);
	angle = acos(dotproduct/multip);
	// angle = dotproduct * 180 / M_PI;
	return (angle);
}

t_point	rotate_axis_angle(t_point vec, t_point axis, float angle)
{
	if (angle == 0)
		return (vec);
	vec = multiply_point_float(vec, cos(angle));
	vec = add_points(vec, multiply_point_float(cross_points(axis, vec), sin(angle)));
	vec = add_points(vec, multiply_point_float( multiply_point_float(axis, dot_points(axis, vec)), (1 - cos(angle))));
	return (vec);
}

// float	length(t_point v)
// {
// 	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
// }

// t_point	get_normal(t_cyl *cyl, t_point p)
// {
// 	float	x;
// 	t_point	ret;

// 	x = dot_points(substract_points(p, cyl->center), cyl->dir);
// 	ret = substract_points(p, add_points(multiply_point_float(cyl->dir, x) , cyl->center));
// 	ret = divide_point_with_float(ret, length(ret));
// 	return (ret);
// }

int	hit_tube(t_cyl *cyl, t_ray ray, float t_min, float t_max, t_besthit *hit_rec)
{
	//Note to self: don't forget to check if inside cyl!!
	float	a;
	float	b;
	float	c;
	float	d;
	float	t0;
	float	t1;
	t_ray	rot_ray;
	t_point	n;
	t_point	p;
	t_point	axis;
	float	angle;
	// t_point	dir_a;
	// t_point	bottom_center;
	t_ray	tmp;


	// printf("cyl dir x: %f, y: %f, z: %f\n", cyl->dir.x, cyl->dir.y, cyl->dir.z);
	angle = calc_angle(new_point(0,1,0), cyl);
	axis = cross_points(cyl->dir, new_point(0,1,0));
	//rotate_axis_angle executes rodrigues calculation

	rot_ray.origin = rotate_axis_angle(substract_points(ray.origin, cyl->center), axis, angle);
	rot_ray.dir = rotate_axis_angle(ray.dir, axis, angle);
	rot_ray.dir = normalize_point(rot_ray.dir);
	//Start calculating intersection with cyl
	a = rot_ray.dir.x * rot_ray.dir.x + rot_ray.dir.z * rot_ray.dir.z;
	b = 2*(rot_ray.origin.x * rot_ray.dir.x + rot_ray.origin.z * rot_ray.dir.z);
	c = rot_ray.origin.x * rot_ray.origin.x + rot_ray.origin.z * rot_ray.origin.z - pow(cyl->diam/2.0, 2);
	d = b*b - 4*a*c;
	if (d < 0)
		return (0);
	t0 = (-b+sqrt(d))/(2*a);
	t1 = (-b-sqrt(d))/(2*a);
	if ((t0 < t1 && t0 >= 0) || t1 < 0)
		t1 = t0;
	if ((t0 < t_min && t1 < t_min) || (t0 > t_max && t1 > t_max))
		return (0);
	if (t1 < 0)
		return (0);

	tmp.dir = cyl->dir;
	tmp.origin = cyl->center;
	if (cyl->dir.x == 0 && cyl->dir.y == 1 && cyl->dir.z == 0)
		p = ray_at(ray, t0);
	else
		p = ray_at(rot_ray, t1);
	// bottom_center = ray_at(tmp, (cyl->height / 2* -1 ));
	// dir_a = substract_points(p, bottom_center);
	// float	x;
	// x = dot_points(normalize_point(dir_a), normalize_point(cyl->dir));
	// n = substract_points(p, add_points((multiply_point_float(normalize_point(cyl->dir), x)), bottom_center));
	//Het aan en uitzetten van bovenstaande heeft invloed op de shading/belichting!
	n = cyl->dir;
	if (p.y < (cyl->center.y - (cyl->height /2))  || p.y > (cyl->center.y + cyl->height / 2))
		return (0);
	hit_rec->color = cyl->color;
		hit_rec->t = t1;
		hit_rec->hit_point = p;
		hit_rec->center = cyl->center;
		if (dot_points(rot_ray.dir, normalize_point(n)) < 0)
		{
			hit_rec->front_face = 1;
			hit_rec->normal = rotate_axis_angle(normalize_point(n), axis, angle * -1);
		}
		else
		{
			hit_rec->front_face = 0;
			hit_rec->normal = rotate_axis_angle(normalize_point(multiply_point_float(normalize_point(n), -1.0)), axis, angle * -1);
		}
	return (1);
}

int	hit_any_cylinder(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max)
{
	int			hit_anything;
	t_besthit	tmp_rec;
	int			i;
	t_list		*tmp;
	t_cyl		*cyl;
	t_point		tmp_center;

	tmp = map_info.lst_cyl;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		cyl = (t_cyl *)tmp->content;
		tmp_center = calc_cap_center(cyl, 0);
		if (hit_cap(cyl, ray, t_min, t_max, &tmp_rec, tmp_center))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		tmp_center = calc_cap_center(cyl, 1);
		if (hit_cap(cyl, ray, t_min, t_max, &tmp_rec, tmp_center))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		if (hit_tube(cyl, ray, t_min, t_max, &tmp_rec))
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