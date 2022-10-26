/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_math_advanced.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:09:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 15:15:39 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include <math.h>

float	dot_points(t_point first, t_point second)
{
	float	result;

	result = first.x * second.x;
	result += first.y * second.y;
	result += first.z * second.z;
	return (result);
}

t_point	normalize_point(t_point dir)
{
	t_point	result;

	result.x = dir.x / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.y = dir.y / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.z = dir.z / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	return (result);
}
