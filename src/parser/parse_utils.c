/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:04:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 18:14:52 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	ft_stofl(char *str)
{
	float	res;
	float	fact;
	int		dot_found;
	int		d;

	res = 0;
	fact = 1;
	dot_found = 0;
	if (*str == '-')
	{
		str++;
		fact = -1;
	}
	while(*str)
	{
		if (*str == '.')
			dot_found = 1;
		d = *str - '0';
		if (d >= 0 && d <= 9)
		{
			if (dot_found)
			{
				fact /= 10.0f;
				res = res * 10.0f + (float)d;
			}
			else
				res = res * 10.0f + (float)d;
		}
		str++;
	}
	return (res * fact);
}