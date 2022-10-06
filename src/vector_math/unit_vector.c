/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_vector.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:23:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 15:16:53 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_coord	unit_vector_coord(t_coord p)
{
	t_coord	result;

	result.x = p.x / (sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
	result.y = p.y / (sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
	result.z = p.z / (sqrt(p.x * p.x + p.y * p.y + p.z * p.z));
	return (result);
}
