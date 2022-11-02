/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   calculate_ambient_color.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 10:48:49 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/02 11:36:07 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	calculate_ambient_color(t_color color, t_amb *amb)
{
	t_color	result_color;
	// t_amb	*ambt; //temporary

	// (void)amb; //temporary
	// ambt = malloc(sizeof(t_amb));
	// ambt->r = 255;//temporary
	// ambt->g = 255;//temporary
	// ambt->b = 255;//temporary
	// ambt->ratio = 1.0; //temporary
	result_color.r = (float)color.r * (float)amb->r / 255.0 * amb->ratio;
	result_color.g = (float)color.g * (float)amb->g / 255.0 * amb->ratio;
	result_color.b = (float)color.b * (float)amb->b / 255.0 * amb->ratio;
	return (result_color);
}
