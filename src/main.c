/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/14 17:50:21 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <stdlib.h>
#include <pthread.h>
#include "libft.h"

static void	minirt_keyhook(mlx_key_data_t keydata, void *ptr)
{
	t_threadinfo	**infos;

	infos = (t_threadinfo **)ptr;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		finish_hook_cleanup_minirt(infos);
		exit(EXIT_SUCCESS);
	}
}

static void	minirt_close(void *ptr)
{
	t_threadinfo	**infos;

	infos = (t_threadinfo **)ptr;
	finish_hook_cleanup_minirt(infos);
	exit(EXIT_SUCCESS);
}

static void	draw_loading_bar(void)
{
	int	i;

	i = 0;
	write(1, "Loading threads: ", 17);
	while (i < 98)
	{
		write(1, "■", 4);
		i++;
	}
	write(1, "\nLoading pixels:  ", 18);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	t_threadinfo	*infos;

	if (argc != 2)
		write_exit("Incorrect args! Usage: ./minirt <mapname>.rt\n", 1);
	init_data(&data, argv);
	init_infos(&infos, &data);
	mlx_key_hook(data.mlx_str.mlx, &minirt_keyhook, &infos);
	mlx_close_hook(data.mlx_str.mlx, &minirt_close, &infos);
	mlx_image_to_window(data.mlx_str.mlx, data.mlx_str.img, 0, 0);
	draw_loading_bar();
	make_threads(&infos);
	mlx_loop(data.mlx_str.mlx);
	mlx_terminate(data.mlx_str.mlx);
	finish_main_cleanup_minirt(&infos);
	return (0);
}
