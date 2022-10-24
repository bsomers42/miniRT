/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   substract.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:14:05 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 17:22:04 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	substract_points(t_coord first, t_coord second)
{
	t_coord	result;

	result.x = first.x - second.x;
	result.y = first.y - second.y;
	result.z = first.z - second.z;
	return (result);
}

t_color	substract_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r - second.r;
	result.g = first.g - second.g;
	result.b = first.b - second.b;
	return (result);
}
