/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cone_cap.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:38:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/14 11:01:42 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_hit	set_hit_rec_cone(t_cone *cone, t_ray ray, double t, t_point cap_center)
{
	t_hit	hit_rec;

	hit_rec.t = t;
	hit_rec.hit_point = ray_at(ray, hit_rec.t);
	hit_rec.color = cone->color;
	hit_rec.center = cap_center;
	set_normal(ray, &hit_rec, cone->dir);
	return (hit_rec);
}

t_point	calc_cap_cone_center(t_cone *cone)
{
	t_point	cap_center;
	t_ray	tmp;

	tmp.dir = normalize_point(cone->dir);
	tmp.origin = cone->top;
	cap_center = ray_at(tmp, cone->height);
	return (cap_center);
}

int	intersect_circle_cone(t_cone *cone, t_ray ray, double t, t_point cap_center)
{
	t_point	p;
	t_point	v;
	double	d;

	p = ray_at(ray, t);
	v = substract_points(p, cap_center);
	d = dot_points(v, v);
	return (sqrt(d) <= cone->radius * 2);
}

int	hit_cone_cap(t_cone *cone, t_ray ray, t_hit *hit_rec)
{
	double	t;
	t_point	cam_to_cntr;
	double	cam_to_normal;

	cam_to_normal = dot_points(cone->dir, ray.dir);
	if (fabs(cam_to_normal) > 0)
	{
		cam_to_cntr = substract_points(calc_cap_cone_center(cone), ray.origin);
		t = (double)dot_points(cam_to_cntr, cone->dir) / (double)cam_to_normal;
		if (t > T_MIN && t < hit_rec->t && \
			intersect_circle_cone(cone, ray, t, calc_cap_cone_center(cone)))
		{
			*hit_rec = set_hit_rec_cone(cone, \
				ray, t, calc_cap_cone_center(cone));
			return (1);
		}
	}
	return (0);
}

int	hit_any_cone_cap(t_parse map_info, t_ray ray, t_hit *hit_rec)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;

	tmp = map_info.lst_cone;
	tmp_rec = *hit_rec;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		if (hit_cone_cap((t_cone *)tmp->content, ray, &tmp_rec))
		{
			hit_anything = i;
			*hit_rec = tmp_rec;
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything >= 0);
}
