/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 12:50:40 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "nodes.h"
#include <stdio.h> //wegggg

float	ft_stofl(char *str);

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_sphere	sp;
	char    **tmp;
	t_list   *node;

	node = (t_list *)malloc(sizeof(t_list));
	tmp = ft_split(line[1], ',');
	sp.x = ft_stofl(tmp[0]);
	sp.y = ft_stofl(tmp[1]);
	sp.z = ft_stofl(tmp[2]);
	free_array(tmp);
	sp.diam = ft_stofl(line[2]);
	tmp = ft_split(line[3], ',');
	sp.r = ft_atoi(tmp[0]);
	sp.g = ft_atoi(tmp[1]);
	sp.b = ft_atoi(tmp[2]);
	printf("[r: %d, g: %d, b: %d]\n", sp.r, sp.g, sp.b);
	free_array(tmp);
	node->content = &sp;
	node->next = NULL;
	ft_lstadd_back(lst, node);
	free_array(line);
}

void	ft_lstadd_pl(t_list **lst, char **line)
{
	t_plane	pl;
	char    **tmp;
	t_list   *node;

	node = (t_list *)malloc(sizeof(t_list));
	tmp = ft_split(line[1], ',');
	pl.x = ft_stofl(tmp[0]);
	pl.y = ft_stofl(tmp[1]);
	pl.z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[2], ',');
	pl.vect_x = ft_stofl(tmp[0]);
	pl.vect_y = ft_stofl(tmp[1]);
	pl.vect_z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[3], ',');
	pl.r = ft_atoi(tmp[0]);
	pl.g = ft_atoi(tmp[1]);
	pl.b = ft_atoi(tmp[2]);
	free_array(tmp);
	node->content = &pl;
	node->next = NULL;
	ft_lstadd_back(lst, node);
	free_array(line);
}

void	ft_lstadd_cy(t_list **lst, char **line)
{
	t_cyl	cy;
	char    **tmp;
	t_list  *node;

	node = (t_list *)malloc(sizeof(t_list));
	tmp = ft_split(line[1], ',');
	cy.x = ft_stofl(tmp[0]);
	cy.y = ft_stofl(tmp[1]);
	cy.z = ft_stofl(tmp[2]);
	free_array(tmp);
	tmp = ft_split(line[2], ',');
	cy.vect_x = ft_stofl(tmp[0]);
	cy.vect_y = ft_stofl(tmp[1]);
	cy.vect_z = ft_stofl(tmp[2]);
	free_array(tmp);
	cy.diam = ft_stofl(line[3]);
	cy.height = ft_stofl(line[4]);
	tmp = ft_split(line[5], ',');
	cy.r = ft_atoi(tmp[0]);
	cy.g = ft_atoi(tmp[1]);
	cy.b = ft_atoi(tmp[2]);
	free_array(tmp);
	node->content = &cy;
	node->next = NULL;
	ft_lstadd_back(lst, node);
	free_array(line);
}
