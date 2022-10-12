/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/12 13:08:25 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include <stdlib.h>
#include <stdio.h>	//misschien weghalen

void	minirt_keyhook(mlx_key_data_t keydata, void *ptr)
{
	t_mlx_str	*mlx_str;

	mlx_str = (t_mlx_str *)ptr;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS);
}

void	minirt_close(void *ptr)
{
	(void)ptr;
	exit(EXIT_SUCCESS);
}



t_sphere	*init_spheres(void)
{
	t_sphere	*spheres;

	spheres = malloc((4) * sizeof(t_sphere));
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
	/* sphere 3 */
	spheres[2].center.x = 0.0;
	spheres[2].center.y = -0.5;
	spheres[2].center.z = -1.0;
	spheres[2].radius = 0.5;
	spheres[2].color.r = 0;
	spheres[2].color.g = 0;
	spheres[2].color.b = 255;
	/* sphere 4 */
	spheres[3].center.x = 0.3;
	spheres[3].center.y = 0.3;
	spheres[3].center.z = -1.5;
	spheres[3].radius = 0.5;
	spheres[3].color.r = 255;
	spheres[3].color.g = 255;
	spheres[3].color.b = 0;
	return (spheres);
}

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.origin.x = 0.0;
	ray.origin.y = -0.3;
	ray.origin.z = 0.0;
	ray.dir.x = 0.0;
	ray.dir.y = 0.0;
	ray.dir.z = 0.0;
	return (ray);
}

int	main(int argc, char *argv[])
{
	t_mlx_str	mlx_str;
	t_sphere	*spheres;
	t_ray		ray;

	if (argc != 2)
		write_exit("wrong input. Usage: ./minirt <mapname>.rt\n", 1);
	// parse_map(argv);
	mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MickeyRT", true);
	// if (!mlx_str.mlx)
		//hier error exitten
	mlx_str.img = mlx_new_image(mlx_str.mlx, WIDTH, HEIGHT);
	mlx_key_hook(mlx_str.mlx, &minirt_keyhook, &mlx_str);
	mlx_close_hook(mlx_str.mlx, &minirt_close, NULL);
	//HIER ANDERE DINGEN DOEN EN OA PIXELS PUTTEN met mlx_put_pixel(img, x value, y value, color) waarbij img in mlx.img zit
	ray = init_ray();
	spheres = init_spheres();
	renderer(spheres, ray, mlx_str);
	mlx_image_to_window(mlx_str.mlx, mlx_str.img, 0, 0);
	mlx_loop(mlx_str.mlx);
	mlx_delete_image(mlx_str.mlx, mlx_str.img);
	mlx_terminate(mlx_str.mlx);
}
