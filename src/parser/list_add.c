/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 15:19:45 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "nodes.h"
#include <stdio.h> //wegggg

float	ft_stofl(char *str);

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_sphere	sp;
	t_sphere	*sp_void;//jma
	char    **tmp;
	// t_list   *node;

	// node = (t_list *)malloc(sizeof(t_list));
	tmp = ft_split(line[1], ',');
	sp.x = ft_stofl(tmp[0]);
	sp.y = ft_stofl(tmp[1]);
	sp.z = ft_stofl(tmp[2]);
	sp.center.x = sp.x; //jma
	sp.center.y = sp.y; //jma
	sp.center.z = sp.z; //jma
	printf("[x: %f, y: %f, z: %f]\n", sp.x, sp.y, sp.z);//jma
	free_array(tmp);
	sp.diam = ft_stofl(line[2]);
	tmp = ft_split(line[3], ',');
	sp.r = ft_atoi(tmp[0]);
	sp.g = ft_atoi(tmp[1]);
	sp.b = ft_atoi(tmp[2]);
	sp.color.r = sp.r * 1.0; //jma
	sp.color.g = sp.g * 1.0; //jma
	sp.color.b = sp.b * 1.0; //jma
	printf("[r: %d, g: %d, b: %d]\n", sp.r, sp.g, sp.b);
	sp_void = malloc(sizeof(t_sphere));//jma
	//check failed //jma
	*sp_void = sp;//jma
	free_array(tmp);
	// node->content = &sp;
	// node->next = NULL;
	ft_lstadd_back(lst, ft_lstnew(sp_void));//node); //jma
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
