/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hit_anything.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 14:57:48 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/07 12:23:07 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hit_anything(t_parse map_info, t_ray ray, t_hit *hit_rec)
{
	int	count;

	count = -1;
	count += hit_any_pl(map_info, ray, hit_rec, hit_rec->t);
	count += hit_any_cap(map_info, ray, hit_rec, hit_rec->t);
	count += hit_any_tube(map_info, ray, hit_rec, hit_rec->t);
	count += hit_any_sp(map_info, ray, hit_rec, hit_rec->t);
	return (count >= 0);
}
