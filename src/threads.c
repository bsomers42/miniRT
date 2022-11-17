/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 13:15:51 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/11 15:36:34 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "threads.h"
#include <unistd.h>

/**
 * @brief check if all pixels are drawn. In that case, print 'DONE!' at stdout
 * 
 * @param info contains all info about the map and threads
 */
static void	check_done(t_threadinfo *info)
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

/**
 * @brief decides the color for this pixel and puts it on the window
 * 
 * @param info	the info to use
 * @param x 	the pixel index on width
 * @param y 	the pixel index on height
 */
static void	fill_pixel(t_threadinfo *info, int x, int y)
{
	t_color	color;
	t_parse	*map_info;

	map_info = (info->data->parse);
	color = antialias_color(*map_info, x, y);
	put_color(info, x, y, color);
	if (pthread_mutex_lock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	info->data->pixels_done++;
	if (pthread_mutex_unlock(&(info->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}

/**
 * @brief fancy way to render the pixels and make the output faster visible
 *  
 * @param ptr points to the info that can be used by the thread
 * @return void* always NULL
 */
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

/**
 * @brief create threads
 * 
 * @param infos array of info of which one of them will be sent to each thread
 */
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
	free(threads);
}
