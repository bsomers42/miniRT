/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   stod_atoi_map_elems.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 16:53:54 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:09 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	atoi_color(char *line, t_color *color)
{
	char	**tmp;

	tmp = ft_split(line, ',');
	malloc_check_arr(tmp);
	if (check_num_of_elems(tmp, 3) != 0)
		write_exit("Wrong information for color\n", 1);
	if (ft_isnumber(tmp[0]) == 0 || ft_isnumber(tmp[1]) == 0 \
	|| ft_isnumber(tmp[2]) == 0)
		write_exit("Wrong information for color\n", 1);
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	check_color_value(color);
	free_array(tmp);
}

void	stod_center(char *line, t_point *center)
{
	char		**tmp;

	tmp = ft_split(line, ',');
	malloc_check_arr(tmp);
	if (check_num_of_elems(tmp, 3) != 0)
		write_exit("Wrong information for coordinates or vector\n", 1);
	check_double_value(tmp[0]);
	check_double_value(tmp[1]);
	check_double_value(tmp[2]);
	center->x = ft_stod(tmp[0]);
	center->y = ft_stod(tmp[1]);
	center->z = ft_stod(tmp[2]);
	free_array(tmp);
}

void	stod_vec(char *line, t_point *vec)
{
	char	**tmp;

	tmp = ft_split(line, ',');
	malloc_check_arr(tmp);
	if (check_num_of_elems(tmp, 3) != 0)
		write_exit("Wrong information for vector\n", 1);
	check_double_value(tmp[0]);
	check_double_value(tmp[1]);
	check_double_value(tmp[2]);
	vec->x = ft_stod(tmp[0]);
	vec->y = ft_stod(tmp[1]);
	vec->z = ft_stod(tmp[2]);
	check_vec_value(*vec);
	*vec = normalize_point(*vec);
	free_array(tmp);
}
