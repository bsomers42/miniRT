/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/02 11:00:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h> //wegggg

void	atoi_color(char *line, t_color *color)
{
	char	**tmp;

	tmp = ft_split(line, ',');
	malloc_check_arr(tmp);
	color->r = ft_atoi(tmp[0]);
	color->g = ft_atoi(tmp[1]);
	color->b = ft_atoi(tmp[2]);
	free_array(tmp);
}

void	stofl_center(char *line, t_point *center)
{
	char		**tmp;

	tmp = ft_split(line, ',');
	malloc_check_arr(tmp);
	center->x = ft_stofl(tmp[0]);
	center->y = ft_stofl(tmp[1]);
	center->z = ft_stofl(tmp[2]);
	free_array(tmp);
}

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_sphere	sp;
	t_sphere	*sp_void;

	stofl_center(line[1], &sp.center);
	sp.diam = ft_stofl(line[2]);
	atoi_color(line[3], &sp.color);
	sp_void = malloc(sizeof(t_sphere));
	if (sp_void == NULL)
		error_exit("malloc", 1);
	*sp_void = sp;
	ft_lstadd_back(lst, ft_lstnew(sp_void));
	free_array(line);
}

void	ft_lstadd_pl(t_list **lst, char **line)
{
	t_plane	pl;
	t_plane	*pl_void;
	char	**tmp;

	stofl_center(line[1], &pl.center);
	tmp = ft_split(line[2], ',');
	malloc_check_arr(tmp);
	pl.dir.x = ft_stofl(tmp[0]);
	pl.dir.y = ft_stofl(tmp[1]);
	pl.dir.z = ft_stofl(tmp[2]);
	free_array(tmp);
	atoi_color(line[3], &pl.color);
	pl_void = malloc(sizeof(t_plane));
	if (pl_void == NULL)
		error_exit("malloc", 1);
	*pl_void = pl;
	ft_lstadd_back(lst, ft_lstnew(pl_void));
	free_array(line);
}

void	ft_lstadd_cy(t_list **lst, char **line)
{
	t_cyl	cy;
	t_cyl	*cy_void;
	char	**tmp;

	stofl_center(line[1], &cy.center);
	tmp = ft_split(line[2], ',');
	malloc_check_arr(tmp);
	cy.dir.x = ft_stofl(tmp[0]);
	cy.dir.y = ft_stofl(tmp[1]);
	cy.dir.z = ft_stofl(tmp[2]);
	free_array(tmp);
	cy.diam = ft_stofl(line[3]);
	cy.height = ft_stofl(line[4]);
	atoi_color(line[5], &cy.color);
	cy_void = malloc(sizeof(t_cyl));
	if (cy_void == NULL)
		error_exit("malloc", 1);
	*cy_void = cy;
	ft_lstadd_back(lst, ft_lstnew(cy_void));
	free_array(line);
}
