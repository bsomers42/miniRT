/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_cylinder_cap.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 16:38:10 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/14 17:29:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

static t_hit	set_hit_rec_cyl(t_cyl *cyl, t_ray ray, double t, t_point cap_center)
{
	t_hit	hit_rec;

	hit_rec.t = t;
	hit_rec.hit_point = ray_at(ray, hit_rec.t);
	hit_rec.color = cyl->color;
	hit_rec.center = cap_center;
	set_normal(ray, &hit_rec, cyl->dir);
	return (hit_rec);
}

static t_point	calc_cap_center(t_cyl *cyl, int side)
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

static int	intersect_circle(t_cyl *cyl, t_ray ray, double t, t_point cap_center)
{
	t_point	p;
	t_point	v;
	double	d;

	p = ray_at(ray, t);
	v = substract_points(p, cap_center);
	d = dot_points(v, v);
	return (sqrt(d) <= cyl->radius);
}

static int	hit_caps(t_cyl *cyl, t_ray ray, t_hit *hit_rec, int side)
{
	double	t;
	t_point	cam_to_cntr;
	double	cam_to_normal;

	cam_to_normal = dot_points(cyl->dir, ray.dir);
	if (fabs(cam_to_normal) > 0)
	{
		cam_to_cntr = substract_points(calc_cap_center(cyl, side), ray.origin);
		t = (double)dot_points(cam_to_cntr, cyl->dir) / (double)cam_to_normal;
		if (t > T_MIN && t < hit_rec->t && \
			intersect_circle(cyl, ray, t, calc_cap_center(cyl, side)))
		{
			*hit_rec = set_hit_rec_cyl(cyl, ray, t, calc_cap_center(cyl, side));
			return (1);
		}
	}
	return (0);
}

int	hit_any_cap(t_parse map_info, t_ray ray, t_hit *hit_rec, int side)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;

	tmp = map_info.lst_cyl;
	tmp_rec = *hit_rec;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		if (hit_caps((t_cyl *)tmp->content, ray, &tmp_rec, side))
		{
			hit_anything = i;
			*hit_rec = tmp_rec;
		}
		tmp = tmp->next;
		i++;
	}
	return (hit_anything >= 0);
}
