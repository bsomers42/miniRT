/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/17 11:04:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 15:17:30 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //voor printf, wegggg!!!

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
			else //jma
				res = res * 10.0f + (float)d;//jma 
		}
		str++;
	}
	return (res * fact);
}