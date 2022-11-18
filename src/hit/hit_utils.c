/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/18 14:32:01 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/18 16:37:46 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	set_front_face_and_normal(t_ray ray, t_besthit *hit_rec, t_point n)
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

	res = (float)pow(vec.x, 2);
	res += (float)pow(vec.y, 2);
	res += (float)pow(vec.z, 2);
	return ((float)sqrt(res));
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
