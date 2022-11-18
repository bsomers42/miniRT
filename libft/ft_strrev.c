/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/25 18:39:23 by bsomers       #+#    #+#                 */
/*   Updated: 2022/11/18 16:41:43 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *rev)
{
	int		len;
	char	*tmp;
	int		i;

	len = ft_strlen(rev);
	tmp = malloc(len * sizeof(char));
	if (tmp == NULL)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i] = rev[len - i - 1];
		i++;
	}
	return (tmp);
}
