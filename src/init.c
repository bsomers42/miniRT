/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 11:16:15 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/01 16:41:40 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "threads.h"

void	init_data(t_data *data, char *argv[])
{
	data->parse = parse_map(argv);
	data->parse->cam.back = multiply_point_float(data->parse->cam.dir, -1.0);
	data->parse->cam.horizontal = calc_horizontal(*(data->parse));
	data->parse->cam.vertical = calc_vertical(*(data->parse));
	data->parse->cam.llc = calculate_lower_left_corner(*(data->parse));
	data->mlx_str.mlx = mlx_init(WIDTH, HEIGHT, "MickeyRT", true);
	if (data->mlx_str.mlx == NULL)
		error_exit("mlx_init failed!\n", 1);
	data->mlx_str.img = mlx_new_image(data->mlx_str.mlx, WIDTH, HEIGHT);
	if (data->mlx_str.img == NULL)
		error_exit("mlx_new_image failed!\n", 1);
	data->pixels_done = 0;
	pthread_mutex_init(&(data->pixel_lock), NULL);
	pthread_mutex_init(&(data->mlx_lock), NULL);
}

void	init_infos(t_threadinfo **infos, t_data *data)
{
	int		i;

	i = 0;
	*infos = malloc(THREADS * sizeof(t_threadinfo));
	if (*infos == NULL)
		error_exit("malloc failed!\n", 1);
	while (i < THREADS)
	{
		(*infos)[i].data = data;
		(*infos)[i].i = i;
		i++;
	}
}
