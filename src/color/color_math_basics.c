/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_math_basics.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:49:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/04 16:11:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	add_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r + second.r;
	result.g = first.g + second.g;
	result.b = first.b + second.b;
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

t_color	multiply_colors(t_color first, t_color second)
{
	t_color	result;

	result.r = first.r * second.r;
	result.g = first.g * second.g;
	result.b = first.b * second.b;
	return (result);
}

t_color	multiply_color_float(t_color color, float t)
{
	t_color	result;

	result.r = (float)color.r * t;
	result.g = (float)color.g * t;
	result.b = (float)color.b * t;
	return (result);
}

t_color	divide_color_with_float(t_color color, float t)
{
	t_color	result;

	result.r = (float)color.r / t;
	result.g = (float)color.g / t;
	result.b = (float)color.b / t;
	return (result);
}
