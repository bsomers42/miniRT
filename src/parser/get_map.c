/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 14:40:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/07 10:40:36 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	check_extension_permission(char *str)
{
	char *tmp;

	tmp = ft_strrev(str);
	if (ft_strncmp(tmp, "tr.", 3) != 0)
		write_exit("Incorrect map extension\n", 1);
	ft_strrev(str);
}

char	*get_map(char *argv[])
{
	int		fd;
	char	*str;
	char	*strdef;

	strdef = NULL;
	check_extension_permission(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		write_exit("Could not find/open map\n", 1);
	while (1)
	{
		str = get_next_line_e(fd);
		if (str == NULL)
			break ;
		if (strdef == NULL)
			strdef = ft_strdup(str);
		else
			strdef = ft_strjoin_fr(strdef, str);
		malloc_check_str(strdef);
		free(str);
	}
	return (strdef);
}
