/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   threads.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 14:07:57 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/12 13:10:54 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H
# include "MLX42.h"
# include <pthread.h>
# include "minirt.h"

typedef struct s_data
{
	t_mlx_str		mlx_str;
	int				pixels_done;
	int				threads_done;
	pthread_mutex_t	pixel_lock;
	pthread_mutex_t	mlx_lock;
	t_parse			*parse;
}	t_data;

typedef struct s_threadinfo
{
	int		i;
	t_data	*data;
}	t_threadinfo;

void	make_threads(t_threadinfo **infos);
void	put_color(t_threadinfo *info, int i, int j, t_color color);
void	init_data(t_data *data, char *argv[]);
void	init_infos(t_threadinfo **infos, t_data *data);

void	finish_hook_cleanup_minirt(t_threadinfo **infos);
void	finish_main_cleanup_minirt(t_threadinfo **infos);
void	free_minirt(t_threadinfo **infos);

#endif
