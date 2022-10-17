/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/17 17:28:39 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <stdlib.h>
#include <stdio.h>	//misschien weghalen
#include <pthread.h>
#include "libft.h"

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
		printf("malloc failed!\n");
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

void	init_infos(t_data *data, t_threadinfo **infos)
{
	int	i;

	i = 0;
	*infos = malloc(THREADS * sizeof(t_threadinfo));
	if (*infos == NULL)
		printf("malloc failed!\n");
	while (i < THREADS)
	{
		(*infos)[i].data = data;
		(*infos)[i].i = i;
		i++;
	}
}

void	init_data(t_data *data)
{
	data->mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MickeyRT", true);
	if (data->mlx_str.mlx == NULL)
		error_exit("mlx_init failed!\n", 1);
	data->mlx_str.img = mlx_new_image(data->mlx_str.mlx, WIDTH, HEIGHT);
	if (data->mlx_str.img == NULL)
		error_exit("mlx_new_image failed!\n", 1);
	data->pixels_done = 0;
	data->spheres = init_spheres();
	data->ray = init_ray();
	pthread_mutex_init(&(data->pixel_lock), NULL);
	pthread_mutex_init(&(data->mlx_lock), NULL);
}

int	main(void)
{
	t_data			data;
	t_threadinfo	*infos;

	init_data(&data);
	init_infos(&data, &infos);
	mlx_key_hook(data.mlx_str.mlx, &minirt_keyhook, &data.mlx_str);
	mlx_close_hook(data.mlx_str.mlx, &minirt_close, NULL);
	mlx_image_to_window(data.mlx_str.mlx, data.mlx_str.img, 0, 0);
	write(1, "loading threads: ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\
				■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n", 313);
	write(1, "loading pixels:  ", 17);
	make_threads(&infos);
	mlx_loop(data.mlx_str.mlx);
	mlx_delete_image(data.mlx_str.mlx, data.mlx_str.img);
	mlx_terminate(data.mlx_str.mlx);
	return (0);
}
