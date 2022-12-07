/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder_cap.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:38:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/07 12:24:47 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_hit	*set_hit_rec_cyl(t_hit *hit_rec, t_cyl *cyl, t_ray ray, float t)
{
	hit_rec->t = t;
	hit_rec->hit_point = ray_at(ray, hit_rec->t);
	hit_rec->color = cyl->color;
	hit_rec->center = cyl->center;
	set_normal(ray, hit_rec, cyl->dir);
	return (hit_rec);
}

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

int	hit_caps(t_cyl *cyl, t_ray ray, float t_max, t_hit *hit_rec)
{
	float	t;
	t_point	polo;
	int		sides;
	float	denom;

	sides = 0;
	cyl->dir = normalize_point(cyl->dir);
	denom = dot_points(cyl->dir, ray.dir);
	while (sides <= 1)
	{
		if (fabs(denom) > 0)
		{
			polo = substract_points(calc_cap_center(cyl, sides), ray.origin);
			t = (float)dot_points(polo, cyl->dir) / (float)denom;
			if (t >= T_MIN && t < t_max && \
			intersect_circle(cyl, ray, t, calc_cap_center(cyl, sides)))
			{
				hit_rec = set_hit_rec_cyl(hit_rec, cyl, ray, t);
				return (1);
			}
		}
		sides++;
	}
	return (0);
}

int	hit_any_cap(t_parse map_info, t_ray ray, t_hit *hit_rec, \
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
		if (hit_caps((t_cyl *)tmp->content, ray, t_max, &tmp_rec))
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
