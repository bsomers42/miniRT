/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   distract.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:14:05 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 12:16:56 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	distract_points(t_coord first, t_coord second)
{
	t_coord	result;

	result.x = first.x - second.x;
	result.y = first.y - second.y;
	result.z = first.z - second.z;
	return (result);
}

t_color	distract_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r - second.r;
	result.g = first.g - second.g;
	result.b = first.b - second.b;
	return (result);
}
