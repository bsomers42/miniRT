/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multiply.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:15:37 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 13:15:28 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	multiply_points(t_coord first, t_coord second)
{
	t_coord	result;

	result.x = first.x * second.x;
	result.y = first.y * second.y;
	result.z = first.z * second.z;
	return (result);
}

t_color	multiply_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r * second.r;
	result.g = first.g * second.g;
	result.b = first.b * second.b;
	return (result);
}

t_coord	multiply_point_float(t_coord point, float t)
{
	t_coord	result;

	result.x = point.x * t;
	result.y = point.y * t;
	result.z = point.z * t;
	return (result);
}

t_color	multiply_color_float(t_color color, float t)
{
	t_color	result;

	result.r = color.r * t;
	result.g = color.g * t;
	result.b = color.b * t;
	return (result);
}
