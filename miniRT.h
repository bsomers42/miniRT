/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 14:48:07 by bsomers       #+#    #+#                 */
/*   Updated: 2022/09/22 14:55:47 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H

# define MINIRT_H

// # include "./libft/libft.h"
# include "./MLX42/include/MLX42/MLX42.h"

# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_mlx_str
{
	void			*mlx;
    void            *img;
}				t_mlx_str;

#endif