/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_sphere.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:46:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 16:43:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen

int	hit_sphere(t_coord sphere_center, float radius, t_ray ray)
{
	t_coord	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = distract_points(ray.origin, sphere_center);
	a = dot_points(ray.dir, ray.dir);
	b = 2.0 * dot_points(oc, ray.dir);
	c = dot_points(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant > 0)
		return (1);
	return (0);
}
