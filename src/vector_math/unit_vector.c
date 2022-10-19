/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_vector.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:23:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/19 13:39:15 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_coord	unit_vector_coord(t_coord dir)
{
	t_coord	result;

	result.x = dir.x / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.y = dir.y / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.z = dir.z / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	return (result);
}
