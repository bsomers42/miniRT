/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder_tube.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 11:37:15 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/08 12:02:52 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	abc_formula(t_ray rot_ray, t_cyl *cyl, float *t)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = rot_ray.dir.x * rot_ray.dir.x + rot_ray.dir.z * rot_ray.dir.z;
	b = 2 * (rot_ray.origin.x * rot_ray.dir.x + rot_ray.origin.z * \
		rot_ray.dir.z);
	c = rot_ray.origin.x * rot_ray.origin.x + rot_ray.origin.z * \
		rot_ray.origin.z - powf(cyl->radius, 2);
	d = b * b - 4 * a * c;
	if (d < 0)
	{
		t[0] = -1;
		t[1] = -1;
		return ;
	}
	t[0] = (-b + sqrtf(d)) / (2 * a);
	t[1] = (-b - sqrtf(d)) / (2 * a);
}

float	quadratic_form_cyl(t_cyl *cyl, t_ray rot_ray, float t_max)
{
	t_point	p;
	float	*t;
	float	t_def;

	t = malloc(3 * sizeof(float));
	abc_formula(rot_ray, cyl, t);
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

void	find_cyl_values(t_cyl *cyl, t_point *p, t_point *n, t_ray tmp)
{
	t_point	bottom_center;
	float	lena;
	float	x;
	t_point	pp;

	bottom_center = ray_at(tmp, (cyl->height / 2 * -1));
	lena = norm(substract_points(*p, bottom_center));
	x = sqrtf(powf(lena, 2.0) - powf(cyl->radius, 2.0));
	tmp.origin = bottom_center;
	pp = ray_at(tmp, x);
	*n = normalize_point(substract_points(*p, pp));
}

int	hit_tube(t_cyl *cyl, t_ray ray, float t_max, t_hit *hit_rec)
{
	t_ray	rot_ray;
	t_point	n;
	t_point	p;
	t_ray	tmp;
	float	t;

	rot_ray = apply_rodrigues(cyl, ray);
	t = quadratic_form_cyl(cyl, rot_ray, t_max);
	if (t == -1)
		return (0);
	tmp.dir = normalize_point(cyl->dir);
	tmp.origin = cyl->center;
	p = ray_at(ray, t);
	find_cyl_values(cyl, &p, &n, tmp);
	if (t >= T_MIN && t < t_max)
	{
		hit_rec->color = cyl->color;
		hit_rec->t = t;
		hit_rec->hit_point = p;
		hit_rec->center = cyl->center;
		set_normal(ray, hit_rec, normalize_point(n));
		return (1);
	}
	return (0);
}

int	hit_any_tube(t_parse map_info, t_ray ray, t_hit *hit_rec, \
	float t_max)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;

	tmp = map_info.lst_cyl;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
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
