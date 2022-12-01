/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/01 09:49:52 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <stdlib.h>
// #include <stdio.h>	//remove in end maybe
#include <pthread.h>
#include "libft.h"

void	minirt_keyhook(mlx_key_data_t keydata, void *ptr)
{
	(void)ptr;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		exit(EXIT_SUCCESS);
}

void	minirt_close(void *ptr)
{
	(void)ptr;
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
	if (argc != 2)
		write_exit("Incorrect args! Usage: ./minirt <mapname>.rt\n", 1);
	init_data(&data, argv);
	init_infos(&infos, &data);
	mlx_key_hook(data.mlx_str.mlx, &minirt_keyhook, NULL);
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
