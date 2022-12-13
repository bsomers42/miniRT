/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_plane.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/02 16:07:31 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/12 15:27:37 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int	hit_plane(t_plane *plane, t_ray ray, double t_max, t_hit *hit_rec)
{
	double	cam_to_normal;
	double	t;
	t_point	n;
	t_point	cam_to_center;

	n = plane->dir;
	cam_to_normal = dot_points(n, ray.dir);
	if (fabs(cam_to_normal) > 0)
	{
		cam_to_center = substract_points(plane->center, ray.origin);
		t = (double)dot_points(cam_to_center, n) / (double)cam_to_normal;
		if (t > T_MIN && t < t_max)
		{
			hit_rec->t = t;
			hit_rec->hit_point = ray_at(ray, hit_rec->t);
			hit_rec->color = plane->color;
			hit_rec->center = plane->center;
			set_normal(ray, hit_rec, n);
			return (1);
		}
	}
	return (0);
}

int	hit_any_pl(t_parse map_info, t_ray ray, t_hit *hit_rec, double t_max)
{
	int			hit_anything;
	t_hit		tmp_rec;
	int			i;
	t_list		*tmp;
	t_plane		*plane;

	tmp = map_info.lst_plane;
	i = 0;
	hit_anything = -1;
	while (tmp)
	{
		plane = (t_plane *)tmp->content;
		if (hit_plane(plane, ray, t_max, &tmp_rec))
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
