/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_math_basics.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:49:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:20 by bsomers       ########   odam.nl         */
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

t_color	multiply_color_double(t_color color, double t)
{
	t_color	result;

	result.r = (double)color.r * t;
	result.g = (double)color.g * t;
	result.b = (double)color.b * t;
	return (result);
}

t_color	divide_color_with_double(t_color color, double t)
{
	t_color	result;

	result.r = (double)color.r / t;
	result.g = (double)color.g / t;
	result.b = (double)color.b / t;
	return (result);
}
