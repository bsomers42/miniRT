/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:45:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/17 17:17:43 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <pthread.h>

void	put_color(t_threadinfo *info, int i, int j, t_color color)
{
	unsigned int	color_hex;

	color_hex = color.r * 16777216 + color.g * 65536 + color.b * 256 + 255;
	if (pthread_mutex_lock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	mlx_put_pixel(info->data->mlx_str.img, i, HEIGHT - j - 1, color_hex);
	if (pthread_mutex_unlock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}
