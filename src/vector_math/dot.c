/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dot.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:20:30 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 12:22:26 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	dot_points(t_coord first, t_coord second)
{
	float	result;

	result = first.x * second.x;
	result += first.y * second.y;
	result += first.z * second.z;
	return (result);
}

float	dot_colors(t_color first, t_color second)
{
	float	result;

	result = first.r * second.r;
	result += first.g * second.g;
	result += first.b * second.b;
	return (result);
}
