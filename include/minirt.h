/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:11:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/10 13:59:35 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

// # define ASPECT_RATIO (float)(16.0 / 9.0)
# define WIDTH 1600
# define HEIGHT 900
# define FOCAL_LENGTH 1.0

# define AA 5 //anti-aliasing
# define THREADS 7
# include "libft.h"
# include "MLX42.h"
# include "color.h"
# include "point.h"
// # include "nodes.h"

typedef struct s_mlx_str
{
	void			*mlx;
	void			*img;
}	t_mlx_str;

typedef struct s_ray
{
	t_point		origin;
	t_vector	dir;
}	t_ray;

typedef struct s_besthit
{
	t_point	hit_point;
	t_point	normal;
	double	t;
	int		front_face;
	t_color	color;
	t_point	center;
}	t_besthit;

typedef struct s_sphere
{
	t_color	color;
	t_point	center;
	float	diam;
}	t_sphere;

typedef struct s_plane
{
	t_point		center;
	t_color		color;
	t_vector	dir;
}	t_plane;

typedef struct s_cyl
{
	t_point		center;
	t_color		color;
	t_vector	dir;
	float		diam;
	float		height;
}	t_cyl;

void	ft_lstadd_sp(t_list **lst, char **line);
void	ft_lstadd_pl(t_list **lst, char **line);
void	ft_lstadd_cy(t_list **lst, char **line);

typedef struct s_amb
{
	float			ratio;
	t_color			color;
}	t_amb;

typedef struct s_cam
{
	t_point	origin;
	t_point	dir;
	int		fov;	
}	t_cam;

typedef struct s_light
{
	t_point	origin;
	float	bright;	
}	t_light;

typedef struct s_parse
{
	t_light	light;
	t_cam	cam;
	t_amb	amb;
	t_list	*lst_sphere;
	t_list	*lst_cyl;
	t_list	*lst_plane;
}	t_parse;

t_parse	*parse_map(char *argv[]);
char	*get_map(char *argv[]);
char	*get_next_line_e(int fd);
void	atoi_color(char *line, t_color *color);
void	stofl_center(char *line, t_point *center);
void	free_minirt(t_parse *parse);
void	malloc_check_arr(char **str);
void	malloc_check_str(char *str);
void	check_vec_value(t_point vec);
void	check_color_value(t_color *color);

int		hit_any_sphere(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max);
int		hit_any_plane(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max);
int		hit_any_cylinder(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max);
int		hit_anything(t_parse map_info, t_ray ray, t_besthit *hit_rec, float t_min, float t_max);

t_color	antialias_color(t_parse map_info, int x, int y);
t_color	point_ray_get_color(t_parse map_info, float i, float j);
t_color	calculate_ambient_color(t_color color, t_amb *amb);
t_point	ray_at(t_ray ray, float t);

void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);
int		error_return(char *message, int return_code);

#endif
