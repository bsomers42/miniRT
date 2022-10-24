/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:07:57 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/24 14:09:06 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_H
# define THREAD_H
# include "MLX42.h"
# include <pthread.h>
# include "minirt.h"

typedef struct s_data
{
	t_mlx_str		mlx_str;
	int				pixels_done;
	pthread_mutex_t	pixel_lock;
	pthread_mutex_t	mlx_lock;
	t_parse			*parse; //over hebben
}	t_data;

typedef struct s_threadinfo
{
	int		i;
	t_data	*data;
}	t_threadinfo;

void	make_threads(t_threadinfo **infos);
void	put_color(t_threadinfo *info, int i, int j, t_color color);

#endif
