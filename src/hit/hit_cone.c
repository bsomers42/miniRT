/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/12 15:28:34 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

void	abc_formula_cone(t_ray rot_ray, double *t)
{
	double	a;
	double	b;
	double	c;
	double	d;

	a = rot_ray.dir.x * rot_ray.dir.x + rot_ray.dir.z * rot_ray.dir.z \
	- rot_ray.dir.y * rot_ray.dir.y;
	b = 2 * (rot_ray.origin.x * rot_ray.dir.x + rot_ray.origin.z * \
		rot_ray.dir.z - rot_ray.origin.y * rot_ray.dir.y);
	c = rot_ray.origin.x * rot_ray.origin.x + rot_ray.origin.z * \
		rot_ray.origin.z - rot_ray.origin.y * rot_ray.origin.y;
	d = b * b - 4 * a * c;
	if (d < 0)
	{
		t[0] = -1;
		t[1] = -1;
		return ;
	}
	t[0] = (-b + sqrt(d)) / (2 * a);
	t[1] = (-b - sqrt(d)) / (2 * a);
}

double	quadratic_form_cone(t_cone *cone, t_ray rot_ray, double t_max)
{
	t_point	p;
	double	t[3];
	double	t_def;

	abc_formula_cone(rot_ray, t);
	if ((t[0] < (double)T_MIN && t[1] < (double)T_MIN) || \
		(t[0] > t_max && t[1] > t_max))
		return (-1);
	if ((t[0] < t[1] && t[0] > (double)T_MIN) || t[1] < (double)T_MIN)
		t[2] = t[0];
	else
		t[2] = t[1];
	p = ray_at(rot_ray, t[2]);
	if (!(p.y > 0 && p.y < cone->height))
	{
		if (t[2] == t[0])
			t[2] = t[1];
		p = ray_at(rot_ray, t[2]);
		if (!(p.y > 0 && p.y < cone->height))
			return (-1);
	}
	t_def = t[2];
	return (t_def);
}

void	find_cone_values(t_cone *cone, t_point p, t_point *n, t_ray tmp)
{
	t_point	bottom_center;
	double	len_a;
	double	x;
	t_point	pp;
	double	tmp_radius;

	bottom_center = ray_at(tmp, (cone->height * -1));
	len_a = norm(substract_points(p, cone->top));
	tmp_radius = len_a * sin(0.785398);
	x = sqrt(pow(len_a, 2.0) - pow(tmp_radius, 2.0));
	pp = ray_at(tmp, x);
	*n = normalize_point(substract_points(p, (pp)));
}

int	hit_cone(t_cone *cone, t_ray ray, double t_max, t_hit *hit_rec)
{
	t_ray	rot_ray;
	t_point	n;
	t_point	p;
	t_ray	tmp;
	double	t;

	rot_ray = apply_rodrigues(cone->dir, cone->top, ray);
	t = quadratic_form_cone(cone, rot_ray, t_max);
	if (t == -1)
		return (0);
	tmp.dir = cone->dir;
	tmp.origin = cone->top;
	p = ray_at(ray, t);
	find_cone_values(cone, p, &n, tmp);
	if (t > T_MIN && t < t_max)
	{
		hit_rec->color = cone->color;
		hit_rec->t = t;
		hit_rec->hit_point = p;
		hit_rec->center = cone->top;
		hit_rec->normal = n;
		return (1);
	}
	return (0);
}

int	hit_any_cone(t_parse map_info, t_ray ray, t_hit *hit_rec, \
	double t_max)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;

	tmp = map_info.lst_cone;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		if (hit_cone((t_cone *)tmp->content, ray, t_max, &tmp_rec))
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
