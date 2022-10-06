/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/06 12:12:23 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>	//misschien weghalen

t_sphere	*init_spheres(void)
{
	t_sphere	*spheres;

	spheres = malloc((2) * sizeof(t_sphere));
	if (spheres == NULL)
		printf("Malloc failed!\n");
	/* sphere 1 */
	spheres[0].center.x = 0.0;
	spheres[0].center.y = 0.0;
	spheres[0].center.z = -1.0;
	spheres[0].radius = 0.5;
	spheres[0].color.r = 255;
	spheres[0].color.g = 0;
	spheres[0].color.b = 0;
	/* sphere 2 */
	spheres[1].center.x = 0.0;
	spheres[1].center.y = -100.5;
	spheres[1].center.z = -1.0;
	spheres[1].radius = 100;
	spheres[1].color.r = 0;
	spheres[1].color.g = 255;
	spheres[1].color.b = 0;
	return (spheres);
}

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.origin.x = 0.0;
	ray.origin.y = 0.0;
	ray.origin.z = 0.0;
	ray.dir.x = 0.0;
	ray.dir.y = 0.0;
	ray.dir.z = 0.0;
	return (ray);
}

int	main(void)
{
	t_mlx_str	mlx_str;
	t_sphere	*spheres;
	t_ray		ray;

	mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MickeyRT", true);
	// if (!mlx_str.mlx)
		//hier error exitten
	mlx_str.img = mlx_new_image(mlx_str.mlx, WIDTH, HEIGHT);
	//HIER ANDERE DINGEN DOEN EN OA PIXELS PUTTEN met mlx_put_pixel(img, x value, y value, color) waarbij img in mlx.img zit
	ray = init_ray();
	spheres = init_spheres();
	renderer(spheres, ray, mlx_str);
	mlx_image_to_window(mlx_str.mlx, mlx_str.img, 0, 0);
	mlx_loop(mlx_str.mlx);
	mlx_delete_image(mlx_str.mlx, mlx_str.img);
	mlx_terminate(mlx_str.mlx);
}
