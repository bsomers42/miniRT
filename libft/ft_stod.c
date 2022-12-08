/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_stod.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/20 10:36:34 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/03 15:25:02 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	convert(double *fact_ptr, double *res_ptr, int d, int dot_found)
{
	double	fact;
	double	res;

	res = *res_ptr;
	fact = *fact_ptr;
	if (dot_found)
	{
		fact /= 10.0f;
		res = res * 10.0f + (double)d;
	}
	else
		res = res * 10.0f + (double)d;
	*res_ptr = res;
	*fact_ptr = fact;
}

double	ft_stod(char *str)
{
	double	res;
	double	fact;
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
	while (*str)
	{
		if (*str == '.')
			dot_found = 1;
		d = *str - '0';
		if (d >= 0 && d <= 9)
			convert(&fact, &res, d, dot_found);
		str++;
	}
	return (res * fact);
}
