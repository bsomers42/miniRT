/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 16:47:20 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/17 14:27:29 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "include/minirt.h"

void	assign_ambient(char *str, int *amb_ptr, t_amb *amb)
{
	char **split;
	char **tmp;

	split = ft_split(str, ' ');
	amb->ratio = ft_stofl(split[1]);
	tmp = ft_split(split[2], 2);
	amb->r = ft_atoi(tmp[0]);
	amb->g = ft_atoi(tmp[1]);
	amb->b = ft_atoi(tmp[2]);
	free(tmp);
	free(split);
	free(str);
	*amb_ptr++;
}

void	assign_camera(char *str, int *cam_ptr, t_cam *cam)
{
	char	**split;
	char	**tmp;

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
	free(str);
	*cam_ptr++;
}

void	assign_light(char *str, int *light_ptr, t_light *light)
{
	char	**split;
	char	**tmp;

	split = ft_split(str, ' ');
	tmp = ft_split(split[1], ',');
	light->x = ft_stofl(tmp[0]);
	light->y = ft_stofl(tmp[1]);
	light->z = ft_stofl(tmp[2]);
	free(tmp);
	light->bright = ft_stofl(split[2]);
	free(split);
	free(str);
	*light_ptr++;
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
	while (map_split_newline[i] != NULL)
	{
		if (ft_isnumber(map_split_newline[i]) == 0)
		{
			if (ft_strncmp(map_split_newline[i], "A ", 2) == 0)
				assign_ambient(map_split_newline[i], &amb, parse->amb);
			else if (ft_strncmp(map_split_newline[i], "C ", 2) == 0)
				assign_camera(map_split_newline[i], &cam, parse->cam);
			else if (ft_strncmp(map_split_newline[i], "L ", 2) == 0)
				assign_light(map_split_newline[i], &light, parse->light);
			// else if (ft_strncmp(map_split_newline[i], "sp ", 3) == 0)
			// else if (ft_strncmp(map_split_newline[i], "pl ", 3) == 0)
			// else if (ft_strncmp(map_split_newline[i], "cy ", 3) == 0)
		}	
		i++;
	}
	if (cam > 1 || cam == 0 || amb > 1 || amb == 0 || light == 0 || light > 1)
		write_exit("Incorrect ambient/light/camera!\n", 1);
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

t_parse	*parse_map(char *argv[])
{
	char    *map_char;
	char	**map_split_newline;
	t_parse	*parse;

	map_char = get_map(argv);
	map_split_newline = ft_split(map_char, '\n');
	assign_to_struct(map_split_newline, parse);
	return (parse);
}