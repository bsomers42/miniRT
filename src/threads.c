/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 13:15:51 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/17 13:49:48 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "threads.h"
#include <unistd.h>

void	check_done(t_threadinfo *info)
{
	if (pthread_mutex_lock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	if (info->data->pixels_done == WIDTH * HEIGHT)
	{
		write(1, "\nDONE!\n", 7);
		info->data->pixels_done++;
	}	
	if (pthread_mutex_unlock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}

static void	fill_pixel(t_threadinfo *info, int x, int y)
{
	t_color	color;

	color = antialias_color(info->data->spheres, info->data->ray, x, y);
	if (pthread_mutex_lock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	put_color(info, x, y, color);
	info->data->pixels_done++;
	if (pthread_mutex_unlock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}

static void	*fill_screen(void *ptr)
{
	t_threadinfo	*info;
	int				x;
	int				y;
	int				count;

	count = 0;
	info = ptr;
	while (count < THREADS * 2)
	{
		y = count % THREADS;
		write(1, "■", 4);
		while (y <= HEIGHT - 1)
		{
			x = (info->i + (count % 2) * THREADS);
			while (x <= WIDTH - 1)
			{
				fill_pixel(info, x, y);
				x += THREADS * 2;
			}
			y += THREADS;
		}
		count++;
	}
	check_done(info);
	return (NULL);
}

void	make_threads(t_threadinfo **infos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(THREADS * sizeof(pthread_t));
	if (threads == NULL)
		error_exit("malloc", 1);
	while (i < THREADS)
	{
		if (pthread_create(&threads[i], NULL, &fill_screen, &(*infos)[i]) != 0)
			error_exit("pthread_create", 1);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		if (pthread_detach(threads[i]) != 0)
			error_exit("pthread_detach", 1);
		i++;
	}
}
