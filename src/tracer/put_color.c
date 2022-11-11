/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:45:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/10 13:22:11 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "MLX42.h"
#include "threads.h"
#include <pthread.h>
#include <math.h>

void	put_color(t_threadinfo *info, int i, int j, t_color color)
{
	unsigned int	color_hex;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	alpha;

	red = color.r * pow(256, 3);
	green = color.g * pow(256, 2);
	blue = color.b * 256;
	alpha = 255;
	color_hex = red + green + blue + alpha;
	if (pthread_mutex_lock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	mlx_put_pixel(info->data->mlx_str.img, WIDTH - i - 1, HEIGHT - j - 1, color_hex);
	if (pthread_mutex_unlock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}
