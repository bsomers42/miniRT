/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 11:41:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/21 14:34:33 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_minirt(t_parse *parse)
{
	t_list	*last;

	last = (t_list *)malloc(sizeof(t_list));
	while (last->next != NULL)
	{
		last = ft_lstlast(parse->lst_cyl);
		free(last->content);
		free(last->next);
		last = ft_lstlast(parse->lst_cyl);
	}
	free(parse->lst_cyl);
	while (last->next != NULL)
	{
		last = ft_lstlast(parse->lst_sphere);
		free(last->content);
		free(last->next);
		last = ft_lstlast(parse->lst_sphere);
	}
	free(parse->lst_sphere);
	while (last->next != NULL)
	{
		last = ft_lstlast(parse->lst_plane);
		free(last->content);
		free(last->next);
		last = ft_lstlast(parse->lst_plane);
	}
	free(parse->lst_plane);
	free(parse);
	free(last);
}

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