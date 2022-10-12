/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:07:57 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/12 15:41:39 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include "MLX42.h"
# include <pthread.h>

typedef struct s_data
{
	t_mlx_str		mlx_str;
	int				*pixels;
	int				pixels_done;
	pthread_mutex_t	pixel_lock;
}	t_data;

typedef struct s_threadinfo
{
	int		i;
	t_data	*data;
}	t_threadinfo;

#endif
