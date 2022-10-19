/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 12:09:19 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

int	main(int argc, char *argv[])
{
	t_mlx_str	mlx_str;
	t_parse		*parse;

	if (argc != 2)
		write_exit("wrong input. Usage: ./minirt <mapname>.rt\n", 1);
	parse = (t_parse *)malloc(sizeof(t_parse));
	//malloc check!
	parse_map(argv, parse);
	mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// if (!mlx_str.mlx)
		//hier error exitten
	mlx_str.img = mlx_new_image(mlx_str.mlx, WIDTH, HEIGHT);
	mlx_key_hook(mlx_str.mlx, &minirt_keyhook, &mlx_str);
	mlx_close_hook(mlx_str.mlx, &minirt_close, NULL);
	//HIER ANDERE DINGEN DOEN EN OA PIXELS PUTTEN met mlx_put_pixel(img, x value, y value, color) waarbij img in mlx.img zit
	mlx_image_to_window(mlx_str.mlx, mlx_str.img, 0, 0);
	mlx_loop(mlx_str.mlx);
	mlx_delete_image(mlx_str.mlx, mlx_str.img);
	mlx_terminate(mlx_str.mlx);
	free_minirt(parse);
}