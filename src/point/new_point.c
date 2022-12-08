/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_point.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 10:48:21 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 14:57:48 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "point.h"

t_point	new_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}
