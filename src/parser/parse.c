/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:47:20 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/23 17:30:51 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	set_coord(char *str, int *x_ptr, int *y_ptr, int *z_ptr)
{
	// int	x;
	// int	y;
	// int	z;
	char **split;

	// x = *x_ptr;
	// y = *y_ptr;
	// z = *z_ptr;
	split = ft_split(str, ',');
	*x_ptr = ft_atoi(split[0]);
	*y_ptr = ft_atoi(split[1]);
	*z_ptr = ft_atoi(split[2]);
	free (split);
	return (0);
}

int	assign_shapes(int sp, int pl, int cy, char **map_split_newline)
{
	int			i;
	t_sphere	sphere;
	char	**sphere_info
	char	**coord;

	i = 0;
	if (sp > 0)
	{
		sphere = malloc(sp * sizeof(t_sphere))
		while (map_split_newline[i] != NULL)
		{
			if (ft_strncmp(map_split_newline[i], "sp ", 3) == 0)
			{
				sphere_info = ft_split(map_split_newline[i], ' ');
				sphere.diam = ft_atoi(sphere_info[2]); //Maar dit moet een float worden!?!?!?!?!???
				set_coord(sphere_info[1], *sphere.coord.x, *sphere.coord.y, *sphere.coord.z);
				set_coord(sphere_info[3], *sphere.color.r, *sphere.color.g, *sphere.color.b);
			}
			i++;
		}
	}
}

int	assign_to_struct(char **map_split_newline)
{
	int	i;
	int sp;
	int pl;
	int	cy;

	i = 0;
	sp = 0;
	pl = 0;
	cy = 0;
	while (map_split_newline[i] != NULL)
	{
		if (ft_isnumber(map_split_newline[i]) == 0)
		{
			if (ft_strncmp(map_split_newline[i], "A ", 2) == 0)
				assign_ambient(map_split_newline, i);
			else if (ft_strncmp(map_split_newline[i], "C ", 2) == 0)
				assign_camera(map_split_newline, i);
			else if (ft_strncmp(map_split_newline[i], "L ", 2) == 0)
				assign_light(map_split_newline, i);
			else if (ft_strncmp(map_split_newline[i], "sp ", 3) == 0)
				sp++;
			else if (ft_strncmp(map_split_newline[i], "pl ", 3) == 0)
				pl++;
			else if (ft_strncmp(map_split_newline[i], "cy ", 3) == 0)
				cy++;
		}	
		i++;
	}
	assign_shapes(sp, pl, cy);
	return (0);
}

int get_map(char *argv[])
{
	int fd;
	char *str;
	char *strdef;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		write_exit("Error when opening map\n", 1);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break;
		strdef = ft_strjoin_fr(strdef, str);
		free (str);		
	}
	return (strdef);
}

int parse_map(char *argv[])
{
	char    *map_char;
	char	**map_split_newline;

	map_char = get_map(argv);
	map_split_newline = ft_split(map_char, '\n');
	assign_to_struct(map_split_newline);
	return (0);
}