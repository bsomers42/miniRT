/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_anything.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:57:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/18 14:24:25 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_anything(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_max)
{
	int	count;

	count = hit_any_plane(map_info, ray, hit_rec, t_max);
	if (count > 0)
		count += hit_any_cylinder(map_info, ray, hit_rec, hit_rec->t);
	else
		count = hit_any_cylinder(map_info, ray, hit_rec, t_max);
	if (count > 0)
		count += hit_any_sphere(map_info, ray, hit_rec, hit_rec->t);
	else
		count = hit_any_sphere(map_info, ray, hit_rec, t_max);
	return (count);
}
