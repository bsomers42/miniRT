/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/11 15:30:35 by jaberkro      ########   odam.nl         */
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
		// cap_center = add_points(tmp.origin, normalize_point(tmp.dir));
		// cap_center = multiply_point_float(cap_center, cyl->height / 2);

		cap_center = ray_at(tmp, (cyl->height / 2));//add_point_float(orig_center, (cyl->height / 2));

	}	
	if (side == 1)
	{
		// cap_center = add_points(tmp.origin, normalize_point(tmp.dir));
		// cap_center = multiply_point_float(cap_center, cyl->height / 2 * -1);

		// tmp.dir.x = tmp.dir.x * -1;
		// tmp.dir.y = tmp.dir.y * -1;
		// tmp.dir.z = tmp.dir.z * -1;

		cap_center = ray_at(tmp, (cyl->height /2 * -1 ));
		// cap_center = ray_at(tmp, (cyl->height /2 * -1 ));

	}
	// ft_printf("Old center: [%f][%f][%f]\nNew center: [%f][%f][%f]\n", \
	// orig_center.x, orig_center.y, orig_center.z, cap_center.x, cap_center.y, cap_center.z);
	
	return (cap_center);
}

int	intersect_circle(t_cyl *cyl, t_ray ray, float t, t_point cap_center)
{
	float	radius;
	t_point	p;
	t_point	v;
	float	d;

	radius = cyl->diam / 2;
	// p = add_points(ray.origin, normalize_point(ray.dir));
	// p = multiply_point_float(p, t);
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

	// cap_center = cyl->center; //weggg

	n = normalize_point(cyl->dir);
	// t = 0;
	denom = dot_points(n, ray.dir);
	if (fabs(denom) > t_min) //Jorien wilt hier suuuuuuupergraag een 0 
	{
		polo = substract_points(cap_center, ray.origin);
		// polo = multiply_points(polo, n);
		t = (float)dot_points(polo, n) / (float)denom;
		if (t >= t_min && t < t_max)
		{
			if (intersect_circle(cyl, ray, t, cap_center))
			{
				hit_rec->t = t;
				hit_rec->hit_point = ray_at(ray, hit_rec->t);
				// hit_rec->hit_point = add_points(ray.origin, normalize_point(ray.dir));
				// hit_rec->hit_point = multiply_point_float(hit_rec->hit_point, t);

				hit_rec->color = cyl->color;
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
	// n = normalize_point(multiply_point_float(cyl->dir, -1.0));
	// // t = 0;
	// denom = dot_points(n, normalize_point(ray.dir));
	// if (denom > t_min)
	// {
	// 	polo = substract_points(cap_center, ray.origin);
	// 	// polo = multiply_points(polo, n);
	// 	t = dot_points(polo, n) / denom;
	// 	if (t >= 0 && t < t_max)
	// 	{
	// 		if (intersect_circle(cyl, ray, t, cap_center))
	// 		{
	// 			hit_rec->t = t;
	// 			hit_rec->hit_point = ray_at(ray, hit_rec->t);
	// 			hit_rec->color = cyl->color;
	// 			// hit_rec->color = new_color(0,255,255);
	// 			hit_rec->center = cyl->center; //deze ook aanpassen naar cap center?
	// 			hit_rec->normal = n;
	// 			return (1);
	// 		}
	// 	}
	// }

	return (0);
}

// t_point	rotate_axis_angle(t_point vec, t_cyl *cyl)
// {
// 	float	angle;
// 	// t_vector	d;
// 	t_point	axis;
// 	// t_point	r_vec;
// 	// t_point	r1_vec;
// 	// t_point	p_vec;

// 	axis = normalize_point(cyl->dir);
// 	angle = acos( divide_float_with_point( dot_points(axis, new_point(0.0,1.0,0.0)) , multiply_points(axis, new_point(0.0, 1.0, 0.0))));
// 	// angle = acos(divide_float_with_point(dot_points(axis, new_point(0.0,1.0,0.0)) , (multiply_points(cyl->dir, new_point(0.0,1.0,0.0)))));
// 	printf("Angle: %f\n", angle);
// 	if (angle == 0)
// 		return (vec);
// 	// d = cross_points(axis, new_point(0.0,1.0,0.0));
// 	// d = multiply_points(d, axis);
// 	// r_vec = substract_points(new_point(0.0,1.0,0.0), d);
// 	// r1_vec = add_points(multiply_point_float(r_vec, cosf(angle)), multiply_point_float(cross_points(axis, r_vec), sinf(angle)));
// 	// p_vec = add_points(d, r1_vec);
// 	vec = add_points( add_points( multiply_point_float(vec, cosf(angle)) , multiply_point_float(cross_points(axis, vec), sinf(angle))) , \
// 	multiply_point_float( multiply_point_float(axis, dot_points(axis, vec)) , (1 - cosf(angle))));

// 	return (vec);
// }

int	hit_tube(t_cyl *cyl, t_ray ray, float t_min, float t_max, t_besthit *hit_rec)
{
	//this works if problem is centered at 0,0,0
	//checking if inside cyl
	float	a;
	float	b;
	float	c;
	float	d;
	float	t0;
	float	t1;
	// t_ray	ray;
	// float	t;
	// float	p;
	// t_ray	cyl_ray;
	// t_point	point;
	// t_point	normal;
	t_point	n;
	t_point	p;
	// float height;
	(void)t_min;
	(void)t_max;

	// a = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z;
	// if (a <= (cyl->diam / 2) * (cyl->diam / 2));
	// {
	// 	a = (cyl->height / 2)
	// 	if (ray.origin.y <= a || ray.origin.y >= a * -1) //then it's inside the cyl
	// 	{	
	// 		//HIER GEGEVENS VAN hit_rec AANPASSEN
	// 		return (1);
	// 	}
	// }
	//////cyl_ray.origin = substract_points(ray.origin, cyl->center);
	// rot_ray.origin = substract_points(ray.origin, cyl->center);
	// rot_ray.origin = rotate_axis_angle(rot_ray.origin, cyl);
	// rot_ray.dir = rotate_axis_angle(ray.dir, cyl);
	a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
	b = 2*(ray.origin.x * ray.dir.x + ray.origin.z * ray.dir.z);
	c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - pow(cyl->diam/2, 2);//((cyl->diam / 2) * (cyl->diam / 2));
	d = b*b - 4*a*c;
	// printf("A");
	if (d < 0)
		return (0);
	t0 = (-b+sqrt(d))/(2*a);
	t1 = (-b-sqrt(d))/(2*a);

	if ((t0 < t1 && t0 >= 0) || t1 < 0)
		t1 = t0;
	//return(x2);
	// if ((x1 < t_min && x2 < t_min) || (x1 > t_max && x2 > t_max))
	// 	return (0);
	if (t1 < 0)
		return (0);
	// printf("B");
	// height = ray.origin.y + t1 * ray.dir.y;
	// if (height < 0 || height > cyl->height)
	// 	return (0);

	//y = 
	// if (t < t_min || t > t_max)
	// 	return (0);
	// else
	// {
	// 	printf("t = %f\n", t);
	// 	hit_rec->color = cyl->color;
	// 	hit_rec->t = t;
	// 	hit_rec->hit_point = ray_at(ray, hit_rec->t);
	// 	hit_rec->center = cyl->center;
	// 	if (dot_points(ray.dir, normalize_point(cyl->dir)) < 0)
	// 	{
	// 		hit_rec->front_face = 1;
	// 		hit_rec->normal = normalize_point(cyl->dir);
	// 	}
	// 	else
	// 	{
	// 		hit_rec->front_face = 0;
	// 		hit_rec->normal = multiply_point_float(normalize_point(cyl->dir), -1.0);
	// 	}
	// }

	// p = cyl->center.y + x2 * ray.dir.y;
	// if (p < 0 || p > cyl->height)
	// 	return (0);
	// return (1);
	
			// printf("p = %f\n", p);
	

	// point = ray_at(ray, t);
	// normal.x = cyl_ray.origin.x * 2;
	// normal.y = 0.0f;
	// normal.z = cyl_ray.origin.z * 2;
	// if (point.y < 0 || point.y > cyl->height)
	// 	return (0);
	// point = ray_at(ray, t);
	t_ray	tmp;

	tmp.dir = cyl->dir;
	tmp.origin = cyl->center;


	p = ray_at(ray, t1);
	t_point	dir_a;
	t_point		cm = ray_at(tmp, (cyl->height /2 * -1 ));
	dir_a = substract_points(p, cm);
	float	x;
	x = dot_points(normalize_point(dir_a), normalize_point(cyl->dir));
	n = substract_points(p, add_points((multiply_point_float(normalize_point(cyl->dir), x)), cm));
	//n = normalize_point(n);
	if (p.y < cm.y || p.y > (cm.y + cyl->height))
		return (0);
	// printf("Hoi?");

		hit_rec->color = cyl->color;
		hit_rec->t = t1;
		hit_rec->hit_point = p;//ray_at(ray, hit_rec->t);
		hit_rec->center = add_points(cm, multiply_point_float(cyl->dir, x));//cyl->center;//Of moet dit x zijn?
		if (dot_points(ray.dir, normalize_point(n)) < 0)
		{
			hit_rec->front_face = 1;
			hit_rec->normal = normalize_point(n);
		}
		else
		{
			hit_rec->front_face = 0;
			hit_rec->normal = normalize_point(multiply_point_float(normalize_point(n), -1.0));
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

	tmp = map_info.lst_cyl; //cy 0.2,0.0,5.0 1.0,0.0,1.0 3 3 255,0,255
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		cyl = (t_cyl *)tmp->content;
		// tmp_center = cyl->center;
		tmp_center = calc_cap_center(cyl, 0);
		if (hit_cap(cyl, ray, t_min, t_max, &tmp_rec, tmp_center))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
			hit_rec->color = new_color(0,255,255);
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
			// hit_rec->color = new_color(255,255,0);
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything >= 0);
}