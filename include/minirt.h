/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 12:11:34 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/17 15:45:43 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 400
# define HEIGHT 400 / 16 * 9
# define VIEWPORT_WIDTH 2.0 * 16.0 / 9.0
# define VIEWPORT_HEIGHT 2.0
# define FOCAL_LENGTH 1.0

# define AA 10 //anti-aliasing
# define THREADS 7
# include "libft.h"
# include "MLX42.h"

typedef struct s_mlx_str
{
	void			*mlx;
	void			*img;
}				t_mlx_str;

typedef struct s_coord
{
	float	x;
	float	y;
	float	z;
}	t_coord;

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_pixel
{
	unsigned int	x;
	unsigned int	y;
}	t_pixel;

typedef struct s_ray
{
	t_coord	origin;
	t_coord	dir;
}	t_ray;

typedef struct s_besthit
{
	t_coord	hit_point;
	t_coord	normal;
	float	t;
	int		front_face;
	t_color	color;
}	t_besthit;

//radius is diameter devided by 2
typedef struct s_sphere
{
	t_coord	center;
	t_color	color;
	float	radius;
}	t_sphere;

typedef struct s_intersect
{
	t_coord	coord;
	t_color	color;
}	t_intersect;

t_coord	add_points(t_coord first, t_coord second);
t_coord	distract_points(t_coord first, t_coord second);
t_coord	multiply_points(t_coord first, t_coord second);
t_coord	multiply_point_float(t_coord point, float t);
t_coord	devide_point_with_float(t_coord point, float t);
float	dot_points(t_coord first, t_coord second);
t_coord	unit_vector_coord(t_coord p);

t_color	add_colors(t_color first, t_color second);
t_color	distract_colors(t_color first, t_color second);
t_color	multiply_colors(t_color first, t_color second);
t_color	multiply_color_float(t_color color, float t);
t_color	devide_color_with_float(t_color color, float t);
float	dot_colors(t_color first, t_color second);

void	renderer(t_sphere *spheres, t_ray ray, t_mlx_str mlx_str);
t_color	new_color(float r, float g, float b);
t_color	decide_color(t_sphere *spheres, t_ray ray, float i, float j);
t_coord	ray_at(t_ray ray, float t);
t_color	ray_color(t_sphere *spheres, t_ray ray);

int		hit_sphere(t_sphere sphere, t_ray ray, float t_min, float t_max, t_besthit *hit_rec);
int		hit_anything(t_sphere *spheres, t_ray ray, t_besthit *hit_rec);

void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);
int		error_return(char *message, int return_code);
t_color	antialias_color(t_sphere *spheres, t_ray ray, int i, int j);

#endif
