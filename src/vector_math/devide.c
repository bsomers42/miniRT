/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   devide.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:16:03 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 13:13:01 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	devide_point_with_float(t_coord point, float t)
{
	t_coord	result;

	result.x = point.x / t;
	result.y = point.y / t;
	result.z = point.z / t;
	return (result);
}

t_color	devide_color_with_float(t_color color, float t)
{
	t_color	result;

	result.r = color.r / t;
	result.g = color.g / t;
	result.b = color.b / t;
	return (result);
}
