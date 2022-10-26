/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:46:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 15:27:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen
#include <math.h>

float	calculate_c(t_point change, float diam)
{
	float	result;

	result = dot_points(change, change) - pow(diam / 2, 2);
	return (result);
}

float	calculate_root(t_sphere *sphere, t_ray ray, float t_min, float t_max)
{
	t_point	change;
	float	a;
	float	half_b;
	float	d;
	float	root;

	change = substract_points(ray.origin, sphere->center);
	a = dot_points(ray.dir, ray.dir);
	half_b = dot_points(change, ray.dir);
	d = half_b * half_b - a * calculate_c(change, sphere->diam);
	if (d < 0.0)
		return (-1.0);
	root = (-half_b - sqrt(d)) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrt(d)) / a;
		if (root < t_min || t_max < root)
			return (-1.0);
	}
	return (root);
}

int	hit_sphere(t_sphere *sphere, t_ray ray, float t_min, float t_max, t_besthit *hit_rec)
{
	float	root;
	t_point	outward_normal;
	float	radius;

	radius = sphere->diam / 2;
	root = calculate_root(sphere, ray, t_min, t_max);
	if (root == -1.0)
		return (0);
	hit_rec->t = root;
	hit_rec->hit_point = ray_at(ray, hit_rec->t);
	hit_rec->color = sphere->color;
	hit_rec->center = sphere->center;
	outward_normal.x = (hit_rec->hit_point.x - sphere->center.x) / radius;
	outward_normal.y = (hit_rec->hit_point.y - sphere->center.y) / radius;
	outward_normal.z = (hit_rec->hit_point.z - sphere->center.z) / radius;
	if (dot_points(ray.dir, outward_normal) < 0)
	{
		hit_rec->front_face = 1;
		hit_rec->normal = outward_normal;
	}
	else
	{
		hit_rec->front_face = 0;
		hit_rec->normal = multiply_point_float(outward_normal, -1.0);
	}
	return (1);
}

int	hit_any_sphere(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max)
{
	int			hit_anything;
	t_besthit	tmp_rec;
	int			i;
	t_list		*tmp;
	t_sphere	*sphere;

	tmp = map_info.lst_sphere;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		if (hit_sphere(sphere, ray, t_min, t_max, &tmp_rec))
		{
			hit_anything = i;
			t_max = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything);
}
