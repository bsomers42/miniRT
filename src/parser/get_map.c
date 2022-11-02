/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 14:40:13 by bsomers       #+#    #+#                 */
/*   Updated: 2022/10/21 14:41:08 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*get_map(char *argv[])
{
	int		fd;
	char	*str;
	char	*strdef;

	strdef = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		write_exit("Error when opening map\n", 1);
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
