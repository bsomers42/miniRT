/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bsomers <bsomers@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/12 15:10:32 by jaberkro      #+#    #+#                 */
/*   Updated: 2022/10/11 11:16:55 by bsomers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief writes a message to stderr and exits
 * 
 * @param message 	the message to print
 * @param exit_code the code to exit with
 */
void	write_exit(char *message, int exit_code)
{
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("malloc", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	free(return_value);
	ft_putstr_fd("mickeyshell: ", STDERR_FILENO);
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
	char	*return_value;
	char	*exit_num;

	exit_num = ft_itoa(exit_code);
	if (exit_num == NULL)
		error_exit("malloc", 1);
	return_value = ft_strjoin("?=", exit_num);
	free(exit_num);
	free(return_value);
	ft_putstr_fd("miniRT: ", STDOUT_FILENO);
	perror(message);
	exit(exit_code);
}

/**
 * @brief prints error message and returns the exit code to use with exit later
 * 
 * @param message 	the message to print about the errno
 * @param return_code the return_code to return
 * @return int 		the return_code to return
 */
int	error_return(char *message, int return_code)
{
	ft_putstr_fd("miniRT: ", STDOUT_FILENO);
	if (return_code == -1)
		set_exit_code(1);
	perror(message);
	return (return_code);
}
