/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:11:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/17 13:15:46 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1920
# define HEIGHT 1080

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_mlx_str
{
	void			*mlx;
	void			*img;
}				t_mlx_str;

typedef struct s_colour
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_colour;

typedef struct s_pixel
{
	unsigned int	x;
	unsigned int	y;
}	t_pixel;

typedef struct s_coord
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	z;
}	t_coord;

//radius is diameter devided by 2
typedef struct s_sphere
{
	t_coord		center;
	t_colour	colour;
	float		radius;
}	t_sphere;

typedef struct s_plane
{
	t_coord		center;
	t_colour	colour;
	float		radius;
}	t_plane;

typedef struct s_intersect
{
	t_coord		coord;
	t_colour	colour;
}	t_intersect;

typedef struct s_amb
{
	float	ratio;
	int		r;
	int		g;
	int		b;	
}	t_amb;

typedef struct s_cam
{
	float	x;
	float	y;
	float	z;
	float	vect_x;
	float	vect_y;
	float	vect_z;
	int		fov;	
}	t_cam;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	float	bright;	
}	t_light;

typedef struct s_parse
{
	t_light *light;
	t_cam	*cam;
	t_amb	*amb;
	t_list	**sp;
	t_list	**pl;
	t_list	**cy;
}


#endif
