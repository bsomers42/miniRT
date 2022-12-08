/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_math_advanced.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:09:22 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 15:11:57 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"
#include <math.h>

double	dot_points(t_point first, t_point second)
{
	double	result;

	result = first.x * second.x;
	result += first.y * second.y;
	result += first.z * second.z;
	return (result);
}

t_point	cross_points(t_point first, t_point second)
{
	t_point	result;

	result.x = first.y * second.z - second.y * first.z;
	result.y = first.z * second.x - second.z * first.x;
	result.z = first.x * second.y - second.x * first.y;
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
