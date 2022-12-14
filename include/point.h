/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:04:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/14 17:45:46 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef t_point	t_vector;

t_point	add_points(t_point first, t_point second);
t_point	substract_points(t_point first, t_point second);
t_point	multiply_point_double(t_point point, double t);
double	dot_points(t_point first, t_point second);
t_point	cross_points(t_point first, t_point second);
t_point	normalize_point(t_point dir);
t_point	new_point(double r, double g, double b);

#endif