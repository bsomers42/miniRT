/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   color.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 14:47:08 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/11 15:34:24 by jaberkro      ########   odam.nl         */
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
t_color	multiply_color_float(t_color color, float t);
t_color	divide_color_with_float(t_color color, float t);
float	dot_colors(t_color first, t_color second);
t_color	clamp_color(t_color color);
t_color	normalize_color(t_color dir);

t_color	new_color(unsigned int r, unsigned int g, unsigned int b);

#endif