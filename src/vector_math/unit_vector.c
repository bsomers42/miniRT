/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unit_vector.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:23:19 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 16:43:36 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h> //weg

t_coord	unit_vector_coord(t_coord dir)
{
	t_coord	result;

	result.x = dir.x / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.y = dir.y / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	result.z = dir.z / (sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z));
	return (result);
}
