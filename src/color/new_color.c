/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   new_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:16:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/26 15:12:47 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"

t_color	new_color(unsigned int r, unsigned int g, unsigned int b)
{
	t_color	result_color;

	result_color.r = r;
	result_color.g = g;
	result_color.b = b;
	return (result_color);
}
