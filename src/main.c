/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/04 14:38:17 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <stdlib.h>
#include <stdio.h>	//remove in end maybe
#include <pthread.h>
#include "libft.h"

void	minirt_keyhook(mlx_key_data_t keydata, void *ptr)
{
	t_mlx_str	*mlx_str;

	mlx_str = (t_mlx_str *)ptr;
	(void)mlx_str; //variable set but not used // jma
	//free things
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS);
}

void	minirt_close(void *ptr)
{
	(void)ptr;
	//free things
	exit(EXIT_SUCCESS);
}

void	draw_loading_bar(void)
{
	int	i;

	i = 0;
	write(1, "loading threads: ", 17);
	while (i < 98)
	{
		write(1, "■", 4);
		i++;
	}
	write(1, "\nloading pixels:  ", 18);
}

// void	func_atexit(void)
// {
// 	system("leaks minirt");
// }

int	main(int argc, char *argv[])
{
	t_data			data;
	t_threadinfo	*infos;

	// atexit(func_atexit);

	(void)argc;
	init_data(&data, argv);
	init_infos(&infos, &data);
	printf("incoming ambient: ratio: %f, rgb: [%u, %u, %u]\n", data.parse->amb.ratio, data.parse->amb.r, data.parse->amb.g, data.parse->amb.b);
	printf("incoming cam: ratio: %f, rgb: [%u, %u, %u]\n", data.parse->amb.ratio, data.parse->amb.r, data.parse->amb.g, data.parse->amb.b);

	mlx_key_hook(data.mlx_str.mlx, &minirt_keyhook, &data.mlx_str);
	mlx_close_hook(data.mlx_str.mlx, &minirt_close, NULL);
	mlx_image_to_window(data.mlx_str.mlx, data.mlx_str.img, 0, 0);
	draw_loading_bar();
	make_threads(&infos);
	mlx_loop(data.mlx_str.mlx);
	mlx_delete_image(data.mlx_str.mlx, data.mlx_str.img);
	mlx_terminate(data.mlx_str.mlx);
	free_minirt(data.parse);
	return (0);
}
