/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:03:00 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 12:17:04 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	add_points(t_coord first, t_coord second)
{
	t_coord	result;

	result.x = first.x + second.x;
	result.y = first.y + second.y;
	result.z = first.z + second.z;
	return (result);
}

t_color	add_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r + second.r;
	result.g = first.g + second.g;
	result.b = first.b + second.b;
	return (result);
}
