/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_add.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:13:12 by bsomers       #+#    #+#                 */
/*   Updated: 2022/12/08 14:58:13 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_lstadd_sp(t_list **lst, char **line)
{
	t_sphere	sp;
	t_sphere	*sp_void;

	if (check_num_of_elems(line, 4) != 0)
		write_exit("Wrong information for sphere\n", 1);
	stofl_center(line[1], &sp.center);
	sp.radius = ft_stofl(line[2]) * 0.5;
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

	if (check_num_of_elems(line, 4) != 0)
		write_exit("Wrong information for plane\n", 1);
	stofl_center(line[1], &pl.center);
	stofl_vec(line[2], &pl.dir);
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

	if (check_num_of_elems(line, 6) != 0)
		write_exit("Wrong information for cylinder\n", 1);
	stofl_center(line[1], &cy.center);
	stofl_vec(line[2], &cy.dir);
	if (cy.dir.x == 0 && cy.dir.y < 0 && cy.dir.z == 0)
		cy.dir.y = cy.dir.y * -1;
	check_double_value(line[3]);
	cy.radius = ft_stofl(line[3]) * 0.5;
	check_double_value(line[4]);
	cy.height = ft_stofl(line[4]);
	atoi_color(line[5], &cy.color);
	cy_void = malloc(sizeof(t_cyl));
	if (cy_void == NULL)
		error_exit("malloc", 1);
	*cy_void = cy;
	ft_lstadd_back(lst, ft_lstnew(cy_void));
	free_array(line);
}
