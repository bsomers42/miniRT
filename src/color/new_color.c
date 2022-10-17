/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:16:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 13:17:51 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	new_color(float r, float g, float b)
{
	t_color	new_color;

	new_color.r = r;
	new_color.g = g;
	new_color.b = b;
	return (new_color);
}