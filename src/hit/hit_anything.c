/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_anything.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:57:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 15:01:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_anything(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max)
{
	return (hit_any_sphere(map_info, ray, hit_rec, t_min, t_max));
}
