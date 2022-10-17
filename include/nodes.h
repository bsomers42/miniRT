/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 11:24:16 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/17 17:33:05 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODES_H
# define NODES_H

# include "libft.h"
# include "minirt.h"

typedef struct  s_node_sp
{
    void *next;
	float	x;
	float	y;
	float	z;
	float	diam;
	int		r;
	int		g;
	int		b;
}	t_node_sp;

typedef struct  s_node_pl
{
    void *next;
	float	x;
	float	y;
	float	z;
	float	vect_x;
	float	vect_y;
	float	vect_z;
	int		r;
	int		g;
	int		b;
}	t_node_pl;

typedef struct  s_node_cy
{
    void *next;
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
}	t_node_cy;

void	ft_lstadd_sp(t_node_sp **lst, char **line);
void	ft_lstadd_pl(t_node_pl **lst, char **line);
void	ft_lstadd_cy(t_node_cy **lst, char **line);

#endif