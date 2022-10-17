/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   renderer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:01:54 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/17 13:47:57 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"

t_color	antialias_color(t_sphere *spheres, t_ray ray, int i, int j)
{
	t_color	color;
	int		k;
	int		l;

	color = new_color(0, 0, 0);
	k = 0;
	while (k < AA)
	{
		l = 0;
		while (l < AA)
		{
			color = add_colors(color, decide_color(spheres, ray, (float)(i) + (float)(k) / (float)(AA), (float)(j) + (float)l / (float)AA));
			l++;
		}
		k++;
	}
	color = devide_color_with_float(color, AA * AA);
	return (color);
}

// void	renderer(t_sphere *spheres, t_ray ray, t_mlx_str mlx_str)
// {
// 	int		i;
// 	int		j;
// 	t_color	color;

// 	j = HEIGHT - 1;
// 	while (j >= 0)
// 	{
// 		i = 0;
// 		while (i < WIDTH)
// 		{
// 			color = antialias_color(spheres, ray, i, j);
// 			// put_color(mlx_str, i, j, color);
// 			// mlx_image_to_window(mlx_str.mlx, mlx_str.img, 0, 0);
// 			i++;
// 		}
// 		j--;
// 	}
// }
