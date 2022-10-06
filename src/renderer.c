/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:01:54 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 13:26:52 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"

void	renderer(t_sphere *spheres, t_ray ray, t_mlx_str mlx_str)
{
	int		i;
	int		j;
	t_color	color;

	(void)spheres;
	(void)ray;
	j = HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIDTH)
		{
			// color.r = 255;
			// color.g = 255;
			// color.b = 0;
			color = decide_color(spheres, ray, i, j);
			put_color(mlx_str, i, j, color);
			i++;
		}
		j--;
	}
}
