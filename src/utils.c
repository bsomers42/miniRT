/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 11:41:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/12 13:13:00 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "threads.h"

void	free_lst(t_list **lst)
{
	t_list	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free(tmp->content);
		free(tmp);
	}
}

void	free_minirt(t_threadinfo **infos)
{
	if (infos[0]->data->parse->lst_plane)
		free_lst(&infos[0]->data->parse->lst_plane);
	if (infos[0]->data->parse->lst_cyl)
		free_lst(&infos[0]->data->parse->lst_cyl);
	if (infos[0]->data->parse->lst_sphere)
		free_lst(&infos[0]->data->parse->lst_sphere);
	free(infos[0]->data->parse);
	mlx_delete_image(infos[0]->data->mlx_str.mlx, infos[0]->data->mlx_str.img);
	free(*infos);
}

void	finish_hook_cleanup_minirt(t_threadinfo **infos)
{
	if (pthread_mutex_lock(&(infos[0]->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	infos[0]->data->pixels_done = WIDTH * HEIGHT + 1;
	infos[0]->data->threads_done++;
	if (infos[0]->data->threads_done == THREADS)
	{
		if (pthread_mutex_unlock(&(infos[0]->data->pixel_lock)) != 0)
			error_exit("pthread_mutex_unlock", 1);
		pthread_mutex_destroy(&(infos[0]->data->pixel_lock));
		free_minirt(infos);
		return ;
	}
	if (pthread_mutex_unlock(&(infos[0]->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
}

void	finish_main_cleanup_minirt(t_threadinfo **infos)
{
	if (pthread_mutex_lock(&(infos[0]->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_lock", 1);
	infos[0]->data->pixels_done = WIDTH * HEIGHT + 1;
	if (pthread_mutex_unlock(&(infos[0]->data->pixel_lock)) != 0)
		error_exit("pthread_mutex_unlock", 1);
	while (1)
	{
		if (pthread_mutex_lock(&(infos[0]->data->pixel_lock)) != 0)
			error_exit("pthread_mutex_lock", 1);
		if (infos[0]->data->threads_done == THREADS)
		{
			if (pthread_mutex_unlock(&(infos[0]->data->pixel_lock)) != 0)
				error_exit("pthread_mutex_unlock", 1);
			pthread_mutex_destroy(&(infos[0]->data->pixel_lock));
			free_minirt(infos);
			return ;
		}
		if (pthread_mutex_unlock(&(infos[0]->data->pixel_lock)) != 0)
			error_exit("pthread_mutex_unlock", 1);
	}
}
