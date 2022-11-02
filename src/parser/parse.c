/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:47:20 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/21 14:40:23 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //voor printf, wegggg!!!

void	assign_ambient(char *str, int *amb_ptr, t_parse *parse)
{
	char	**split;
	char	**tmp;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	parse->amb.ratio = ft_stofl(split[1]);
	tmp = ft_split(split[2], ',');
	malloc_check_arr(tmp);
	parse->amb.r = ft_atoi(tmp[0]);
	parse->amb.g = ft_atoi(tmp[1]);
	parse->amb.b = ft_atoi(tmp[2]);
	free_array(tmp);
	free_array(split);
	*amb_ptr = *amb_ptr + 1;
}

void	assign_camera(char *str, int *cam_ptr, t_parse *parse)
{
	char	**split;
	char	**tmp;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	tmp = ft_split(split[1], ',');
	malloc_check_arr(tmp);
	parse->cam.x = ft_stofl(tmp[0]);
	parse->cam.y = ft_stofl(tmp[1]);
	parse->cam.z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(split[2], ',');
	malloc_check_arr(tmp);
	parse->cam.vect_x = ft_stofl(tmp[0]);
	parse->cam.vect_y = ft_stofl(tmp[1]);
	parse->cam.vect_z = ft_stofl(tmp[2]);
	free_array(tmp);
	parse->cam.fov = ft_atoi(split[3]);
	free_array(split);
	*cam_ptr = *cam_ptr + 1;
}

void	assign_light(char *str, int *light_ptr, t_parse *parse)
{
	char	**split;
	char	**tmp;

	split = ft_split(str, ' ');
	malloc_check_arr(split);
	tmp = ft_split(split[1], ',');
	malloc_check_arr(tmp);
	parse->light.x = ft_stofl(tmp[0]);
	parse->light.y = ft_stofl(tmp[1]);
	parse->light.z = ft_stofl(tmp[2]);
	free_array(tmp);
	parse->light.bright = ft_stofl(split[2]);
	free_array(split);
	*light_ptr = *light_ptr + 1;
}

void	test_lists(t_list **lst_sphere)
{
	t_list		*last;
	t_sphere	*sphere;

	last = ft_lstlast(*lst_sphere);
	sphere = (t_sphere *)last->content;
	printf("[TESTr: %d, g: %d, b: %d]\n", sphere->color.r, \
	sphere->color.g, sphere->color.b);
}

int	assign_to_struct(char **map_split_n, t_parse *parse)
{
	int	i;
	int	amb;
	int	cam;
	int	light;

	i = 0;
	amb = 0;
	cam = 0;
	light = 0;
	parse->lst_sphere = NULL;
	while (map_split_n[i] != NULL)
	{
		if (ft_strncmp(map_split_n[i], "A ", 2) == 0)
			assign_ambient(map_split_n[i], &amb, parse);
		else if (ft_strncmp(map_split_n[i], "C ", 2) == 0)
			assign_camera(map_split_n[i], &cam, parse);
		else if (ft_strncmp(map_split_n[i], "L ", 2) == 0)
			assign_light(map_split_n[i], &light, parse);
		else if (ft_strncmp(map_split_n[i], "sp ", 3) == 0)
			ft_lstadd_sp(&(parse->lst_sphere), ft_split(map_split_n[i], ' '));
		else if (ft_strncmp(map_split_n[i], "pl ", 3) == 0)
			ft_lstadd_pl(&(parse->lst_plane), ft_split(map_split_n[i], ' '));
		else if (ft_strncmp(map_split_n[i], "cy ", 3) == 0)
			ft_lstadd_cy(&(parse->lst_cyl), ft_split(map_split_n[i], ' '));
		i++;
	}
	test_lists(&(parse->lst_sphere));
	if (cam > 1 || cam == 0 || amb > 1 || amb == 0 || light == 0 || light > 1)
		write_exit("Incorrect ambient/light/camera!\n", 1);
	return (0);
}

t_parse	*parse_map(char *argv[])
{
	char	*map_char;
	char	**map_split_newline;
	t_parse	*parse;

	parse = (t_parse *)malloc(sizeof(t_parse));
	if (parse == NULL)
		error_exit("malloc", 1);
	map_char = get_map(argv);
	map_split_newline = ft_split(map_char, '\n');
	malloc_check_arr(map_split_newline);
	free(map_char);
	assign_to_struct(map_split_newline, parse);
	free_array(map_split_newline);
	return (parse);
}
