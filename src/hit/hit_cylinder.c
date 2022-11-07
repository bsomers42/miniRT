/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/07 17:18:20 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h> ///wegggg

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
	denom = dot_points(n, normalize_point(ray.dir));
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
				hit_rec->center = cyl->center; //deze ook aanpassen naar cap center?
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

int	hit_tube(t_cyl *cyl, t_ray ray, float t_min, float t_max, t_besthit *hit_rec)
{
	//this works if problem is centered at 0,0,0
	//checking if inside cyl
	float	a;
	float	b;
	float	c;
	float	d;
	float	x1;
	float	x2;
	float	t;
	t_point	point;
	t_point	normal;

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
	t = 0;
	a = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z;
	b = 2*(ray.origin.x * ray.dir.x + ray.origin.z * ray.dir.z);
	c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - ((cyl->diam / 2) * (cyl->diam / 2));
	d = b*b - 4*a*c;
	if (d < 0)
		return (0);
	x1 = (-b+sqrt(d))/(2*a);
	x2 = (-b-sqrt(d))/(2*a);
	if (x1 > x2)
		t = x2;
	if (t < 0)
		t = x1;
	// if ((x1 < t_min && x2 < t_min) || (x1 > t_max && x2 > t_max))
	// 	return (0);
	if (t < t_min || t > t_max)
		return (0);
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
	point = ray_at(ray, t);
	normal.x = point.x * 2;
	normal.y = 0.0f;
	normal.z = point.z * 2;
	if (point.y < 0 || point.y > cyl->height)
		return (0);
	point = ray_at(ray, t);
			printf("t = %f\n", t);
		hit_rec->color = cyl->color;
		hit_rec->t = t;
		hit_rec->hit_point = ray_at(ray, hit_rec->t);
		hit_rec->center = cyl->center;
		if (dot_points(ray.dir, normalize_point(normal)) < 0)
		{
			hit_rec->front_face = 1;
			hit_rec->normal = normalize_point(normal);
		}
		else
		{
			hit_rec->front_face = 0;
			hit_rec->normal = multiply_point_float(normalize_point(normal), -1.0);
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
			hit_rec->color = new_color(255,255,255);
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
			hit_rec->color = new_color(255,255,0);
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything >= 0);
}