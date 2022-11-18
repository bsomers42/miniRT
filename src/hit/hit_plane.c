/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 16:07:31 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/18 16:40:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int	hit_plane(t_plane *plane, t_ray ray, float t_min, float t_max, t_hit *hit_rec)
{
	float	denom;
	float	t;
	t_point	n;
	t_point	polo;

	n = normalize_point(plane->dir);
	denom = dot_points(n, ray.dir);
	if (fabs(denom) > 0)
	{
		polo = substract_points(plane->center, ray.origin);
		t = (float)dot_points(polo, n) / (float)denom;
		if (t >= t_min && t < t_max)
		{
			hit_rec->t = t;
			hit_rec->hit_point = ray_at(ray, hit_rec->t);
			hit_rec->color = plane->color;
			hit_rec->center = plane->center;
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
	return (0);
}

int	hit_any_pl(t_parse map_info, t_ray ray, t_hit *hit_rec, float t_max)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;
	t_plane		*plane;
	float t_min = 0.01;

	tmp = map_info.lst_plane;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		plane = (t_plane *)tmp->content;
		if (hit_plane(plane, ray, t_min, t_max, &tmp_rec))
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
