/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:47:20 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 13:46:20 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "nodes.h"
#include <stdio.h> //voor printf, wegggg!!!

void	assign_ambient(char *str, int *amb_ptr, t_amb *amb)
{
	char **split;
	char **tmp;

	amb = (t_amb *)malloc(sizeof(t_amb));
	split = ft_split(str, ' ');
	amb->ratio = ft_stofl(split[1]);
	tmp = ft_split(split[2], ',');
	amb->r = ft_atoi(tmp[0]);
	amb->g = ft_atoi(tmp[1]);
	amb->b = ft_atoi(tmp[2]);
	free(tmp);
	free(split);
	*amb_ptr = *amb_ptr + 1;
}

void	assign_camera(char *str, int *cam_ptr, t_cam *cam)
{
	char	**split;
	char	**tmp;

	cam = (t_cam *)malloc(sizeof(t_cam));
	split = ft_split(str, ' ');
	tmp = ft_split(split[1], ',');
	cam->x = ft_stofl(tmp[0]);
	cam->y = ft_stofl(tmp[1]);
	cam->z = ft_stofl(tmp[2]);
	free(tmp);
	tmp = ft_split(split[2], ',');
	cam->vect_x = ft_stofl(tmp[0]);
	cam->vect_y = ft_stofl(tmp[1]);
	cam->vect_z = ft_stofl(tmp[2]);
	free(tmp);
	cam->fov = ft_atoi(split[3]);
	free(split);
	*cam_ptr = *cam_ptr + 1;
}

void	assign_light(char *str, int *light_ptr, t_light *light)
{
	char	**split;
	char	**tmp;

	light = (t_light *)malloc(sizeof(t_light));
	split = ft_split(str, ' ');
	tmp = ft_split(split[1], ',');
	light->x = ft_stofl(tmp[0]);
	light->y = ft_stofl(tmp[1]);
	light->z = ft_stofl(tmp[2]);
	free(tmp);
	light->bright = ft_stofl(split[2]);
	free(split);
	*light_ptr = *light_ptr + 1;
}

void	test_lists(t_list **lst_sphere)
{
	t_list *last;
	t_sphere	*sphere;

	last = ft_lstlast(*lst_sphere);
	sphere = (t_sphere *)last->content;
	printf("[r: %d, g: %d, b: %d]\n", sphere->r, sphere->g, sphere->b);
}

int	assign_to_struct(char **map_split_newline, t_parse *parse)
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
	
	while (map_split_newline[i] != NULL)
	{
		// if (ft_isnumber(map_split_newline[i]) == 0)
		// {
			if (ft_strncmp(map_split_newline[i], "A ", 2) == 0)
				assign_ambient(map_split_newline[i], &amb, parse->amb);
			else if (ft_strncmp(map_split_newline[i], "C ", 2) == 0)
				assign_camera(map_split_newline[i], &cam, parse->cam);
			else if (ft_strncmp(map_split_newline[i], "L ", 2) == 0)
				assign_light(map_split_newline[i], &light, parse->light);
			else if (ft_strncmp(map_split_newline[i], "sp ", 3) == 0)
				ft_lstadd_sp(&(parse->lst_sphere), ft_split(map_split_newline[i], ' '));
			// else if (ft_strncmp(map_split_newline[i], "pl ", 3) == 0)
			// else if (ft_strncmp(map_split_newline[i], "cy ", 3) == 0)
		// }	
		i++;
	}
	test_lists(&(parse->lst_sphere));
	if (cam > 1 || cam == 0 || amb > 1 || amb == 0 || light == 0 || light > 1)
		write_exit("Incorrect ambient/light/camera!\n", 1);
	return (0);
}

char *get_map(char *argv[])
{
	int fd;
	char *str;
	char *strdef;

	strdef = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		write_exit("Error when opening map\n", 1);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break;
		if (strdef == NULL)
			strdef = ft_strdup(str);
		else
			strdef = ft_strjoin_fr(strdef, str);
		free (str);		
	}
	return (strdef);
}

t_parse	*parse_map(char *argv[])//, t_parse *parse)
{
	char    *map_char;
	char	**map_split_newline;
	t_parse *parse;

	parse = (t_parse *)malloc(sizeof(t_parse));

	map_char = get_map(argv);
	map_split_newline = ft_split(map_char, '\n');
	free(map_char);
	assign_to_struct(map_split_newline, parse);
	free_array(map_split_newline);
	return (parse);
}
