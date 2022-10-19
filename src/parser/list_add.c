/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 17:53:18 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //wegggg

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_sphere	sp;
	t_sphere	*sp_void;//jma
	char    **tmp;

	tmp = ft_split(line[1], ',');
	sp.center.x = ft_stofl(tmp[0]);
	sp.center.y = ft_stofl(tmp[1]);
	sp.center.z = ft_stofl(tmp[2]);
	free_array(tmp);
	sp.diam = ft_stofl(line[2]);
	tmp = ft_split(line[3], ',');
	sp.color.r = ft_atoi(tmp[0]) * 1.0;
	sp.color.g = ft_atoi(tmp[1]) * 1.0;
	sp.color.b = ft_atoi(tmp[2]) * 1.0;
	printf("[r: %d, g: %d, b: %d]\n", sp.color.r, sp.color.g, sp.color.b);
	sp_void = malloc(sizeof(t_sphere));//jma
	*sp_void = sp;//jma
	free_array(tmp);
	ft_lstadd_back(lst, ft_lstnew(sp_void));//node); //jma
	free_array(line);
}

void	ft_lstadd_pl(t_list **lst, char **line)
{
	t_plane	pl;
	t_plane	*pl_void;
	char    **tmp;

	tmp = ft_split(line[1], ',');
	pl.center.x = ft_stofl(tmp[0]);
	pl.center.y = ft_stofl(tmp[1]);
	pl.center.z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[2], ',');
	pl.vect_x = ft_stofl(tmp[0]);
	pl.vect_y = ft_stofl(tmp[1]);
	pl.vect_z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[3], ',');
	pl.color.r = ft_atoi(tmp[0]) * 1.0;
	pl.color.g = ft_atoi(tmp[1]) * 1.0;
	pl.color.b = ft_atoi(tmp[2]) * 1.0;
	free_array(tmp);
	pl_void = malloc(sizeof(t_plane));//jma
	*pl_void = pl;//jma
	ft_lstadd_back(lst, ft_lstnew(pl_void));//node); //jma
	free_array(line);
}

void	ft_lstadd_cy(t_list **lst, char **line)
{
	t_cyl	cy;
	t_cyl	*cy_void;
	char    **tmp;

	tmp = ft_split(line[1], ',');
	cy.center.x = ft_stofl(tmp[0]);
	cy.center.y = ft_stofl(tmp[1]);
	cy.center.z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[2], ',');
	cy.vect_x = ft_stofl(tmp[0]);
	cy.vect_y = ft_stofl(tmp[1]);
	cy.vect_z = ft_stofl(tmp[2]);
	free_array(tmp);
	cy.diam = ft_stofl(line[3]);
	cy.height = ft_stofl(line[4]);
	tmp = ft_split(line[5], ',');
	cy.color.r = ft_atoi(tmp[0]) * 1.0;
	cy.color.g = ft_atoi(tmp[1]) * 1.0;
	cy.color.b = ft_atoi(tmp[2]) * 1.0;
	free_array(tmp);
	cy_void = malloc(sizeof(t_cyl));//jma
	*cy_void = cy;//jma
	ft_lstadd_back(lst, ft_lstnew(cy_void));//node); //jma
	free_array(line);
}
