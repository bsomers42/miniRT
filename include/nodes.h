/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/19 11:30:41 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODES_H
# define NODES_H

# include "libft.h"
# include "minirt.h"

// typedef struct s_list
// {
// 	void			*content;
// 	struct s_list 	*next;
// }				t_list;  //Staat al in libft.h!

typedef struct  s_sphere
{
	float	x;
	float	y;
	float	z;
	float	diam;
	int		r;
	int		g;
	int		b;
}	t_sphere;

typedef struct  s_plane
{
	float	x;
	float	y;
	float	z;
	float	vect_x;
	float	vect_y;
	float	vect_z;
	int		r;
	int		g;
	int		b;
}	t_plane;

typedef struct  s_cyl
{
	float	x;
	float	y;
	float	z;
	float	vect_x;
	float	vect_y;
	float	vect_z;
	float	diam;
	float	height;
	int		r;
	int		g;
	int		b;
}	t_cyl;

void	ft_lstadd_sp(t_list **lst, char **line);
void	ft_lstadd_pl(t_list **lst, char **line);
void	ft_lstadd_cy(t_list **lst, char **line);

#endif