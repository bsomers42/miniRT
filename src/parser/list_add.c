/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/17 11:15:03 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "nodes.h"

float	ft_stofl(char *str);

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_list	*sp;
    char    **tmp;

    sp->next = NULL;
    sp->type = sp;
    tmp = ft_split(line[1], ',');
    sp->x = ft_stofl(tmp[0]); //vertalen naar float!
    sp->y = ft_stofl(tmp[1]);
    sp->z = ft_stofl(tmp[2]);
    free(tmp);
    sp->diam = ft_stofl(line[2]); //vertalen naar float!
    tmp = ft_split(line[3], ',');
    sp->r = tmp[0];
    sp->g = tmp[1];
    sp->b = tmp[2];
    free(tmp);
	if (*lst == NULL)
		*lst = sp;
	else
	{
		last = ft_lstlast(*lst);
		last->next = sp;
	}
}

void	ft_lstadd_pl(t_list **lst, char **line)
{
	t_list	*pl;
    char    **tmp;
    t_list  *last;

    pl->next = NULL;
    pl->type = pl;
    tmp = ft_split(line[1], ',');
    pl->x = ft_stofl(tmp[0]); //vertalen naar float!
    pl->y = ft_stofl(tmp[1]);
    pl->z = ft_stofl(tmp[2]);
    free(tmp);
    tmp = ft_split(line[2], ',');
    pl->vect_x = tmp[0];
    pl->vect_y = tmp[1];
    pl->vect_z = tmp[2];
    free(tmp);
    tmp = ft_split(line[3], ',');
    pl->r = tmp[0];
    pl->g = tmp[1];
    pl->b = tmp[2];
    free(tmp);
	if (*lst == NULL)
		*lst = pl;
	else
	{
		last = ft_lstlast(*lst);
		last->next = pl;
	}
}

void	ft_lstadd_cy(t_list **lst, char **line)
{
	t_list	*cy;
    char    **tmp;

    cy->next = NULL;
    cy->type = pl;
    tmp = ft_split(line[1], ',');
    cy->x = ft_stofl(tmp[0]); //vertalen naar float!
    cy->y = ft_stofl(tmp[1]);
    cy->z = ft_stofl(tmp[2]);
    free(tmp);
    tmp = ft_split(line[2], ',');
    cy->vect_x = ft_stofl(tmp[0]);
    cy->vect_y = ft_stofl(tmp[1]);
    cy->vect_z = ft_stofl(tmp[2]);
    free(tmp);
    cy->diam = ft_stofl(line[3]); //float
    cy->height = ft_stofl(line[4]);
    tmp = ft_split(line[5], ',');
    cy->r = tmp[0];
    cy->g = tmp[1];
    cy->b = tmp[2];
    free(tmp);
	if (*lst == NULL)
		*lst = cy;
	else
	{
		last = ft_lstlast(*lst);
		last->next = cy;
	}
}