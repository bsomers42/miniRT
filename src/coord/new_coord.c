/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_coord.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/24 10:48:21 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 10:49:58 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_coord	new_coord(float x, float y, float z)
{
	t_coord	new_coord;

	new_coord.x = x;
	new_coord.y = y;
	new_coord.z = z;
	return (new_coord);
}
