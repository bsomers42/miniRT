/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:54:42 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/22 14:55:28 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	main()
{
	t_mlx_str	mlx_str;

	mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	// if (!mlx_str.mlx)
		//hier error exitten
	mlx_str.img = mlx_new_image(mlx_str.mlx, WIDTH, HEIGHT);
	//HIER ANDERE DINGEN DOEN EN OA PIXELS PUTTEN met mlx_put_pixel(img, x value, y value, color) waarbij img in mlx.img zit
	mlx_image_to_window(mlx_str.mlx, mlx_str.img, 0, 0);
	mlx_loop(mlx_str.mlx);
	mlx_delete_image(mlx_str.mlx, mlx_str.img);
	mlx_terminate(mlx_str.mlx);
}