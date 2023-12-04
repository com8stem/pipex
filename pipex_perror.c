/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_perror.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:58:46 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 21:59:21 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_errorout(char *errorname)
{
	perror(errorname);
	exit(EXIT_FAILURE);
}

void	ft_errorout_file(t_info info)
{
	if (info.infile_fd == -1)
		perror(info.argv[1]);
	if (info.outfile_fd == -1)
		perror(info.argv[info.argc - 1]);
	exit(EXIT_FAILURE);
}

void	ft_put_error_cmd(char *error, char *cmd, int index)
{
	char	*error_message;
	char	*tmp;

	tmp = cmd;
	error_message = ft_strjoin(&cmd[index], error);
	free(tmp);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_put_error_cmd_without_free(char *error, char *cmd, int index)
{
	char	*error_message;

	error_message = ft_strjoin(&cmd[index], error);
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit (EXIT_FAILURE);
}

void	ft_argc_error(char *error)
{
	ft_putendl_fd(error, STDERR_FILENO);
	exit (EXIT_FAILURE);
}
