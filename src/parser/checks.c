/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 17:51:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/07 17:22:35 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_vec_value(t_point vec)
{
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || \
	vec.z < -1 || vec.z > 1)
		write_exit("Wrong vector value\n", 1);
}

void	check_color_value(t_color *color)
{
	if (color->r > 255 || color->r < 0 || color->g > 255 || \
	color->g < 0 || color->b > 255 || color->b < 0)
		write_exit("Invalid color value\n", 1);
}
