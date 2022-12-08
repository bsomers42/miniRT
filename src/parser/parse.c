/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:47:20 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/08 16:47:16 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //voor printf, wegggg!!!

void	assign_ambient(char *str, int *amb_ptr, t_parse *parse)
{
	char	**split;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	if (check_num_of_elems(split, 3) != 0)
		write_exit("Wrong information for ambient (A)\n", 1);
	check_double_value(split[1]);
	parse->amb.ratio = ft_stod(split[1]);
	if (parse->amb.ratio < 0 || parse->amb.ratio > 1)
		write_exit("Wrong ambient lighting ratio. [0.0,1.0]\n", 1);
	atoi_color(split[2], &parse->amb.color);
	free_array(split);
	*amb_ptr = *amb_ptr + 1;
}

void	assign_camera(char *str, int *cam_ptr, t_parse *parse)
{
	char	**split;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	if (check_num_of_elems(split, 4) != 0)
		write_exit("Wrong information for camera (C)\n", 1);
	stod_center(split[1], &parse->cam.origin);
	stod_vec(split[2], &parse->cam.dir);
	parse->cam.fov = ft_atoi(split[3]);
	if (parse->cam.fov <= 0 || parse->cam.fov > 180)
		write_exit("Wrong FOV value\n", 1);
	free_array(split);
	*cam_ptr = *cam_ptr + 1;
}

void	assign_light(char *str, int *light_ptr, t_parse *parse)
{
	char	**split;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	if (check_num_of_elems(split, 3) != 0)
		write_exit("Wrong information for light (L)\n", 1);
	stod_center(split[1], &parse->light.origin);
	check_double_value(split[2]);
	parse->light.bright = ft_stod(split[2]);
	if (parse->light.bright < 0 || parse->light.bright > 1)
		write_exit("Wrong light brightness ratio. [0.0,1.0]\n", 1);
	free_array(split);
	*light_ptr = *light_ptr + 1;
}

void	assign_to_struct(char **map_split_n, t_parse *parse)
{
	int	*cla;

	cla = ft_calloc(3, sizeof(int));
	while (*map_split_n != NULL)
	{
		if (ft_strncmp(*map_split_n, "A ", 2) == 0)
			assign_ambient(*map_split_n, &cla[2], parse);
		else if (ft_strncmp(*map_split_n, "C ", 2) == 0)
			assign_camera(*map_split_n, &cla[0], parse);
		else if (ft_strncmp(*map_split_n, "L ", 2) == 0)
			assign_light(*map_split_n, &cla[1], parse);
		else if (ft_strncmp(*map_split_n, "sp ", 3) == 0)
			ft_lstadd_sp(&(parse->lst_sphere), ft_split(*map_split_n, ' '));
		else if (ft_strncmp(*map_split_n, "pl ", 3) == 0)
			ft_lstadd_pl(&(parse->lst_plane), ft_split(*map_split_n, ' '));
		else if (ft_strncmp(*map_split_n, "cy ", 3) == 0)
			ft_lstadd_cy(&(parse->lst_cyl), ft_split(*map_split_n, ' '));
		else if (ft_strncmp(*map_split_n, "# ", 2) != 0)
			write_exit("Excessive characters included/information missing\n", 1);
		map_split_n++;
	}
	check_number_of_cla(cla[0], cla[2], cla[1]);
	free (cla);
}

t_parse	*parse_map(char *argv[])
{
	char	*map_char;
	char	**map_split_newline;
	t_parse	*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	if (parse == NULL)
		error_exit("malloc", 1);
	parse->lst_sphere = NULL;
	parse->lst_plane = NULL;
	parse->lst_cyl = NULL;
	map_char = get_map(argv);
	map_split_newline = ft_split(map_char, '\n');
	malloc_check_arr(map_split_newline);
	free(map_char);
	assign_to_struct(map_split_newline, parse);
	free_array(map_split_newline);
	return (parse);
}
