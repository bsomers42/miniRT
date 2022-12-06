/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/06 15:29:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	set_normal(t_ray ray, t_hit *hit_rec, t_point n)
{
	if (dot_points(ray.dir, n) < 0)
		hit_rec->normal = n;
	else
		hit_rec->normal = multiply_point_float(n, -1.0);
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
