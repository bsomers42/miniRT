/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:47:08 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/08 14:59:17 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

t_color	add_colors(t_color first, t_color second);
t_color	substract_colors(t_color first, t_color second);
t_color	multiply_colors(t_color first, t_color second);
t_color	multiply_color_double(t_color color, double t);
t_color	divide_color_with_double(t_color color, double t);
double	dot_colors(t_color first, t_color second);
t_color	clamp_color(t_color color);
t_color	normalize_color(t_color dir);

t_color	new_color(unsigned int r, unsigned int g, unsigned int b);

#endif