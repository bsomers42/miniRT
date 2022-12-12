/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:46:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 15:10:55 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

double	calculate_c(t_point change, double radius)
{
	double	result;

	result = dot_points(change, change) - powf(radius, 2);
	return (result);
}

double	calculate_root(t_sphere *sphere, t_ray ray, double t_max)
{
	t_point	change;
	double	a;
	double	half_b;
	double	d;
	double	root;

	change = substract_points(ray.origin, sphere->center);
	a = dot_points(ray.dir, ray.dir);
	half_b = dot_points(change, ray.dir);
	d = half_b * half_b - a * calculate_c(change, sphere->radius);
	if (d < 0.0)
		return (-1.0);
	root = (-half_b - sqrt(d)) / a;
	if (root < T_MIN || t_max < root)
	{
		root = (-half_b + sqrt(d)) / a;
		if (root < T_MIN || t_max < root)
			return (-1.0);
	}
	return (root);
}

int	hit_sphere(t_sphere *sphere, t_ray ray, double t_max, t_hit *hit_rec)
{
	double		root;
	t_vector	normal;

	root = calculate_root(sphere, ray, t_max);
	if (root == -1.0)
		return (0);
	hit_rec->t = root;
	hit_rec->hit_point = ray_at(ray, hit_rec->t);
	hit_rec->color = sphere->color;
	hit_rec->center = sphere->center;
	normal.x = (hit_rec->hit_point.x - sphere->center.x) / sphere->radius;
	normal.y = (hit_rec->hit_point.y - sphere->center.y) / sphere->radius;
	normal.z = (hit_rec->hit_point.z - sphere->center.z) / sphere->radius;
	if (dot_points(ray.dir, normal) < 0)
		hit_rec->normal = normal;
	else
		hit_rec->normal = multiply_point_double(normal, -1.0);
	return (1);
}

int	hit_any_sp(t_parse map_info, t_ray ray, t_hit *hit_rec, double t_max)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;
	t_sphere	*sphere;

	tmp = map_info.lst_sphere;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		sphere = (t_sphere *)tmp->content;
		if (hit_sphere(sphere, ray, t_max, &tmp_rec))
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
