/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:45:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 16:53:42 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include <stdio.h> //weghalen

void	put_color(t_mlx_str mlx_str, int i, int j, t_color color)
{
	unsigned int	color_hex;

	color_hex = color.r * 16777216 + color.g * 65536 + color.b * 256 + 255;
	printf("color:%x\n", color_hex);
	mlx_put_pixel(mlx_str.img, i, HEIGHT - j - 1, color_hex);
}
