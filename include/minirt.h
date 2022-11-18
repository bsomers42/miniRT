/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jaberkro <jaberkro@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 15:11:47 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/11/18 17:43:24 by jaberkro      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIDTH 1600
# define HEIGHT 900
# define FOCAL_LENGTH 1.0

# define T_MIN 0.01

# define AA 3 //anti-aliasing
# define THREADS 7
# include "libft.h"
# include "MLX42.h"
# include "color.h"
# include "point.h"

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

typedef struct s_hit
{
	t_point	hit_point;
	t_point	normal;
	double	t;
	int		front_face;
	t_color	color;
	t_point	center;
}	t_hit;

typedef struct s_sphere
{
	t_color	color;
	t_point	center;
	float	radius;
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
	float		radius;
	float		height;
}	t_cyl;

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

//parsing
t_parse	*parse_map(char *argv[]);
char	*get_map(char *argv[]);
char	*get_next_line_e(int fd);
void	ft_lstadd_sp(t_list **lst, char **line);
void	ft_lstadd_pl(t_list **lst, char **line);
void	ft_lstadd_cy(t_list **lst, char **line);
void	atoi_color(char *line, t_color *color);
void	stofl_center(char *line, t_point *center);
void	stofl_vec(char *line, t_point *vec);

//parsing checks
void	malloc_check_arr(char **str);
void	malloc_check_str(char *str);
void	check_vec_value(t_point vec);
void	check_color_value(t_color *color);
int		check_num_of_elems(char **array, int num);
void	check_float_value(char *str);
void	check_number_of_cla(int cam, int amb, int light);

//utils
void	free_minirt(t_parse *parse);

//tracer
int		hit_any_sp(t_parse map_info, t_ray ray, t_hit *hit_rec, float t_max);
int		hit_any_pl(t_parse map_info, t_ray ray, t_hit *hit_rec, float t_max);
int		hit_any_cyl(t_parse map_info, t_ray ray, t_hit *hit_rec, float t_max);
int		hit_anything(t_parse map_info, t_ray ray, t_hit *hit_rec);

float	norm(t_point vec);
int		hit_both_caps(t_cyl *cyl, t_ray ray, float t_max, t_hit *tmp_rec);

//tracer utils
void	set_front_face_and_normal(t_ray ray, t_hit *hit_rec, t_point n);
float	norm(t_point vec);
float	calc_angle(t_point upaxis, t_cyl *cyl);

t_color	antialias_color(t_parse map_info, int x, int y);
t_color	point_ray_get_color(t_parse map_info, float i, float j);
t_point	ray_at(t_ray ray, float t);
// t_color	point_ray_get_color(t_parse map_info, t_ray ray);

t_point	calc_vertical(t_parse map_info, t_point backward);
t_point	calc_horizontal(t_parse map_info, t_point backward);
t_point	add_vertical_position(t_point dir, t_parse map_info, float j);
t_point	add_horizontal_position(t_point dir, t_parse map_info, float i);
t_point	calc_lower_left_corner(t_parse map_info);

void	error_exit(char *message, int exit_code);
void	write_exit(char *message, int exit_code);

#endif
