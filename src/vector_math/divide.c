/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   devide.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:16:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 17:21:24 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	divide_point_with_float(t_coord point, float t)
{
	t_coord	result;

	result.x = point.x / t;
	result.y = point.y / t;
	result.z = point.z / t;
	return (result);
}

t_color	divide_color_with_float(t_color color, float t)
{
	t_color	result;

	result.r = color.r / t;
	result.g = color.g / t;
	result.b = color.b / t;
	return (result);
}
