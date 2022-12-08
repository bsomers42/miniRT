/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color_math_advanced.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:52:45 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:21 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

double	dot_colors(t_color first, t_color second)
{
	double	result;

	result = first.r * second.r;
	result += first.g * second.g;
	result += first.b * second.b;
	return (result);
}

t_color	clamp_color(t_color color)
{
	t_color	new_color;

	if (color.r > 255)
		new_color.r = 255;
	if (color.g > 255)
		new_color.g = 255;
	if (color.b > 255)
		new_color.b = 255;
	return (new_color);
}

t_color	normalize_color(t_color dir)
{
	t_color	result;

	result.r = dir.r / 255;
	result.g = dir.g / 255;
	result.b = dir.b / 255;
	return (result);
}
