/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:46:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/19 16:03:26 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen
#include <math.h>

int	hit_sphere(t_sphere *sphere, t_ray ray, float t_min, float t_max, t_besthit *hit_rec)
{
	t_coord	change;
	float	a;
	float	half_b;
	float	c;
	float	d;
	float	sqrtd;
	float	root;
	t_coord outward_normal;

	change.x = ray.origin.x - sphere->center.x;
	change.y = ray.origin.y - sphere->center.y;
	change.z = ray.origin.z - sphere->center.z;
	a = dot_points(ray.dir, ray.dir);
	half_b = dot_points(change, ray.dir);
	c = dot_points(change, change) - sphere->diam * sphere->diam;
	d = half_b * half_b - a * c;
	if (d < 0)
		return (0);
	sqrtd = sqrt(d);
	root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	hit_rec->t = root;
	hit_rec->hit_point = ray_at(ray, hit_rec->t);
	hit_rec->normal.x = hit_rec->hit_point.x - sphere->center.x / sphere->diam;
	hit_rec->normal.y = hit_rec->hit_point.y - sphere->center.y / sphere->diam;
	hit_rec->normal.z = hit_rec->hit_point.z - sphere->center.z / sphere->diam;
	hit_rec->color = sphere->color;
	hit_rec->center = sphere->center;
	outward_normal.x = (hit_rec->hit_point.x - sphere->center.x) / sphere->diam;
	outward_normal.y = (hit_rec->hit_point.y - sphere->center.y) / sphere->diam;
	outward_normal.z = (hit_rec->hit_point.z - sphere->center.z) / sphere->diam;
	if (dot_points(ray.dir, outward_normal) < 0)
	{
		hit_rec->front_face = 1;
		hit_rec->normal = outward_normal;
	}
	else
	{
		hit_rec->front_face = 0;
		hit_rec->normal = outward_normal;
	}
	return (1);
}

int	hit_anything(t_list *spheres, t_ray ray, t_besthit *hit_rec)
{
	float		closest_so_far;
	int			hit_anything;
	t_besthit	tmp_rec;
	int			i;
	t_list		*tmp;
	t_sphere	*sphere;

	tmp = spheres;
	i = 0;
	closest_so_far = INFINITY;
	hit_anything = -1;
	while (tmp) // amount spheres
	{
		sphere = (t_sphere *)tmp->content;
		if (hit_sphere(sphere, ray, 0, closest_so_far, &tmp_rec))
		{
			hit_anything = i;
			closest_so_far = tmp_rec.t;
			*hit_rec = tmp_rec;
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything);
}
