/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:10:32 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/12/06 11:41:35 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include <stdio.h> //laten staan voor perror!

/**
 * @brief writes a message to stderr and exits
 * 
 * @param message 	the message to print
 * @param exit_code the code to exit with
 */
void	write_exit(char *message, int exit_code)
{
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("malloc", 1);
	free(exit_num);
	ft_putstr_fd("Error\nminiRT: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}

/**
 * @brief uses perror to print an error message and exits
 * 
 * @param message 	the message to given to perror
 * @param exit_code the code to exit with
 */
void	error_exit(char *message, int exit_code)
{
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("malloc", 1);
	free(exit_num);
	ft_putstr_fd("miniRT: ", STDOUT_FILENO);
	perror(message);
	exit(exit_code);
}
