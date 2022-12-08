/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing_checks.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/04 17:51:50 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:10 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	check_double_value(char *str)
{
	int	i;
	int	dot;

	i = 0;
	dot = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			dot++;
		else if ((!ft_isdigit(str[i]) && i != 0) || \
		(str[i] == '-' && i != 0) || (str[i] == '+' && i != 0))
		{
			dot = -1;
			break ;
		}
		i++;
	}
	if (!ft_isdigit(str[i - 1]) || dot > 2 || dot < 0)
		write_exit("Invalid double value\n", 1);
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

int	check_num_of_elems(char **array, int num)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
		i++;
	if (i != num)
		return (1);
	return (0);
}

void	check_number_of_cla(int cam, int amb, int light)
{
	if (cam == 0 || amb == 0 || light == 0)
		write_exit("Missing ambient/light/camera!\n", 1);
	if (cam > 1 || amb > 1 || light > 1)
		write_exit("Use only one ambient, one light and one camera!\n", 1);
}
