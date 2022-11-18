/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_point.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 10:48:21 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/18 14:33:32 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	new_point(float x, float y, float z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}
