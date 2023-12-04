/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:23:59 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/01 18:42:15 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exec_filetopipe(int *pipefd, t_info info, int i)
{
	char	**cmd;

	cmd = ft_cmd_set(info, info.argv[i]);
	if (cmd[0] != NULL)
	{
		dup2(info.infile_fd, STDIN_FILENO);
		close(info.infile_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd[0], cmd, NULL);
		perror("execve");
	}
	exit(EXIT_FAILURE);
}

void	ft_exec_pipetopipe(int *pipefd, t_info info, int i)
{
	char	**cmd;

	cmd = ft_cmd_set(info, info.argv[i]);
	if (cmd[0] != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		execve(cmd[0], cmd, NULL);
		perror("execve");
	}
	exit(EXIT_FAILURE);
}

void	ft_exec_pipetofile(t_info info, int i)
{
	char	**cmd;

	cmd = ft_cmd_set(info, info.argv[i]);
	if (cmd[0] != NULL)
	{
		dup2(info.outfile_fd, STDOUT_FILENO);
		close(info.outfile_fd);
		execve(cmd[0], cmd, NULL);
		perror("execve");
	}
	exit(EXIT_FAILURE);
}

void	ft_setpipe_parent(int *pipefd)
{
	dup2 (pipefd[0], STDIN_FILENO);
	close (pipefd[1]);
	close (pipefd[0]);
}

void	ft_exec(t_info info, int i)
{
	int		pipefd[2];
	int		parent;

	if (pipe(pipefd) == -1)
		ft_errorout("pipe");
	parent = fork();
	if (parent == -1)
		ft_errorout("fork");
	if (parent == 0)
	{
		if (i == 2 || (i == 3 && info.heredoc_flag == 1))
			ft_exec_filetopipe(pipefd, info, i);
		else if (i + 2 == info.argc
			|| (i + 1 == info.argc && info.heredoc_flag == 1))
			ft_exec_pipetofile(info, i);
		else
			ft_exec_pipetopipe(pipefd, info, i);
	}
	ft_setpipe_parent(pipefd);
}
