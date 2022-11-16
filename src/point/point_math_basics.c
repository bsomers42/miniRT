/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point_math_basics.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:03:26 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/16 12:56:52 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	add_points(t_point first, t_point second)
{
	t_point	result;

	result.x = first.x + second.x;
	result.y = first.y + second.y;
	result.z = first.z + second.z;
	return (result);
}

t_point	substract_points(t_point first, t_point second)
{
	t_point	result;

	result.x = first.x - second.x;
	result.y = first.y - second.y;
	result.z = first.z - second.z;
	return (result);
}

t_point	multiply_points(t_point first, t_point second)
{
	t_point	result;

	result.x = first.x * second.x;
	result.y = first.y * second.y;
	result.z = first.z * second.z;
	return (result);
}

t_point	multiply_point_float(t_point point, float t)
{
	t_point	result;

	result.x = point.x * t;
	result.y = point.y * t;
	result.z = point.z * t;
	return (result);
}

t_point	divide_point_with_float(t_point point, float t)
{
	t_point	result;

	result.x = point.x / t;
	result.y = point.y / t;
	result.z = point.z / t;
	return (result);
}
