/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_anything.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:57:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/03 13:24:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //wegegggg

int	hit_anything(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max)
{
	int	count;

	count = hit_any_plane(map_info, ray, hit_rec, t_min, t_max);
	// return (hit_any_sphere(map_info, ray, hit_rec, t_min, t_max));
	// printf("Count = [%d]\n", count);
	if (count == 1)
		count += hit_any_sphere(map_info, ray, hit_rec, t_min, hit_rec->t);
	else
		count = hit_any_sphere(map_info, ray, hit_rec, t_min, t_max);
	//zelfde verhaal voor cyl
	if (count >= 1)
		count += hit_any_cylinder(map_info, ray, hit_rec, t_min, hit_rec->t);
	else
		count = hit_any_cylinder(map_info, ray, hit_rec, t_min, t_max);
	return (count);
}
