/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_vector.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:23:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 11:05:54 by jaberkro      ########   odam.nl         */
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

// t_color	unit_vector_color(t_color dir)
// {
// 	t_color	result;

// 	result.r = dir.r / 255;
// 	result.g = dir.g / 255;
// 	result.b = dir.b / 255;
// 	return (result);
// }
