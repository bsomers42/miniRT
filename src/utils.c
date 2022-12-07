/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 11:41:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/07 16:19:22 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	free_lst_cyl(t_parse *parse)
// {
// 	t_list	*last;

// 	last = (t_list *)malloc(sizeof(t_list));
// 	while (last->next != NULL)
// 	{
// 		last = ft_lstlast(parse->lst_cyl);
// 		free(last->content);
// 		free(last->next);
// 		last = ft_lstlast(parse->lst_cyl);
// 	}
// 	free(parse->lst_cyl);
// 	free(last);
// }

// void	free_lst_sphere(t_parse *parse)
// {
// 	t_list	*last;

// 	last = (t_list *)malloc(sizeof(t_list));
// 	while (last->next != NULL)
// 	{
// 		last = ft_lstlast(parse->lst_sphere);
// 		free(last->content);
// 		free(last->next);
// 		last = ft_lstlast(parse->lst_sphere);
// 	}
// 	free(parse->lst_sphere);
// 	free(last);
// }

// void	free_lst_plane(t_parse *parse)
// {
// 	t_list	*last;

// 	// last = (t_list *)malloc(sizeof(t_list));
// 	while (parse->lst_plane)
// 	{
// 		last = (*parse->lst_plane).next;
// 		free((*parse->lst_plane).content);//->next);
// 		free((void*)parse->lst_plane);
// 		*parse->lst_plane = *last;
// 		// free(last->content);
// 		// last = ft_lstlast(parse->lst_plane);
// 	}
// 	// if (parse->lst_plane)
// 		// free(parse->lst_plane);
// 	// free(last);
// }

// void	free_minirt(t_parse *parse)
// {
// 	free_lst_plane(parse);
// 	free_lst_cyl(parse);
// 	free_lst_sphere(parse);
// 	free(parse);
// }

void	free_lst(t_list **lst)
{
	t_list	*curr;

	while (*lst)
	{
		curr = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = curr;
	}
}

void	free_minirt(t_parse *parse)
{
	free_lst(&parse->lst_plane);
	free_lst(&parse->lst_cyl);
	free_lst(&parse->lst_sphere);
	// free(parse);
}
