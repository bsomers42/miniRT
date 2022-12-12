/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_color.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:45:02 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/12 20:04:06 by jaberkro      ########   odam.nl         */
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
	t_mlx_str		str;

	str = info->data->mlx_str;
	red = color.r * pow(255, 3);
	green = color.g * pow(255, 2);
	blue = color.b * 255;
	color_hex = red + green + blue + 255;
	if (pthread_mutex_lock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	mlx_put_pixel(str.img, WIDTH - i - 1, HEIGHT - j - 1, color_hex);
	if (pthread_mutex_unlock(&(info->data->mlx_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}
