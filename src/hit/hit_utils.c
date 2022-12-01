/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/01 12:46:02 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	set_front_face_and_normal(t_ray ray, t_hit *hit_rec, t_point n)
{
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
}

float	norm(t_point vec)
{
	float	res;

	res = (float)powf(vec.x, 2);
	res += (float)powf(vec.y, 2);
	res += (float)powf(vec.z, 2);
	return ((float)sqrtf(res)); //jma sqrt of sqrtf?
}

float	calc_angle(t_point upaxis, t_cyl *cyl)
{
	float	angle;
	float	multip;
	float	dotproduct;

	multip = (norm(upaxis) * norm(cyl->dir));
	dotproduct = dot_points(upaxis, cyl->dir);
	angle = acos(dotproduct / multip);
	return (angle);
}
