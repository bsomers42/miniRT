/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 17:51:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/15 15:12:02 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_float_value(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			dot++;
		if (ft_isdigit(str[i]) == 0)
		{
			dot = -1;
			break;
		}
		i++;
	}
	if (dot > 1 || dot < 0)
		write_exit("Invalid float value\n", 1);
}

void	check_vec_value(t_point vec)
{
	if (vec.x < -1 || vec.x > 1 || vec.y < -1 || vec.y > 1 || \
	vec.z < -1 || vec.z > 1)
		write_exit("Wrong vector value. [-1.0,1.0]\n", 1);
	if (vec.x == 0 && vec.y == 0 && vec.z == 0)
		write_exit("Empty vector value, please indicate direction\n", 1);
}

void	check_color_value(t_color *color)
{
	if (color->r > 255 || color->r < 0 || color->g > 255 || \
	color->g < 0 || color->b > 255 || color->b < 0)
		write_exit("Invalid color value. [0-255]\n", 1);
}

int		check_num_of_elems(char **array, int num)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i != num)
		return (1);
	return (0);
}
