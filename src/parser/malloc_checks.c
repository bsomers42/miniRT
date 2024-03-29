/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   malloc_checks.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 17:09:09 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/12 10:47:58 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	malloc_check_str(char *str)
{
	if (str == NULL)
		error_exit("malloc", 1);
}

void	malloc_check_arr(char **str)
{
	if (str == NULL)
		error_exit("malloc", 1);
}
