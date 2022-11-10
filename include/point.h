/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   point.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 15:04:52 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/10 13:52:08 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
}	t_point;

typedef t_point	t_vector;

t_point	add_points(t_point first, t_point second);
t_point	substract_points(t_point first, t_point second);
t_point	multiply_points(t_point first, t_point second);
t_point	add_point_float(t_point point, float t);
t_point	multiply_point_float(t_point point, float t);
t_point	divide_point_with_float(t_point point, float t);
float	dot_points(t_point first, t_point second);
t_point	cross_points(t_point first, t_point second);
t_point	normalize_point(t_point dir);
t_point	new_point(float r, float g, float b);

#endif