/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   clamp.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 16:47:59 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 17:19:09 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_color	clamp_color(t_color color)
{
	t_color	new_color;

	if (color.r < 0)
		new_color.r = 0;
	if (color.g < 0)
		new_color.g = 0;
	if (color.b < 0)
		new_color.b = 0;
	if (color.r > 255)
		new_color.r = 255;
	if (color.g > 255)
		new_color.g = 255;
	if (color.b > 255)
		new_color.b = 255;
	return (new_color);
}
