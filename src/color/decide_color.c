/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   decide_color.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:26:28 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/06 15:34:57 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //weghalen

t_color	decide_color(t_sphere *spheres, t_ray ray, int i, int j)
{
	t_color	color;
	float	u;
	float	v;
	t_coord	lower_left_corner;

	(void)spheres;
	lower_left_corner.x = ray.origin.x - VIEWPORT_WIDTH / 2;
	lower_left_corner.y = ray.origin.y - VIEWPORT_HEIGHT / 2;
	lower_left_corner.x = ray.origin.z - FOCAL_LENGTH;
	u = (float)i / (WIDTH - 1);
	v = (float)j / (HEIGHT - 1);
	ray.dir.x = lower_left_corner.x + u * VIEWPORT_WIDTH - ray.origin.x;
	ray.dir.y = lower_left_corner.y + v * VIEWPORT_HEIGHT - ray.origin.y;
	ray.dir.z = lower_left_corner.z - ray.origin.z;
	printf("ray dirs - x:%f, y:%f, z:%f\n", ray.dir.x, ray.dir.y, ray.dir.z);
	color = new_color(u * 255, v * 255, 0.25 * 255); // werkt wel
	// color = ray_color(ray);
	return (color);
}
