/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_info_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:00:24 by kishizu           #+#    #+#             */
/*   Updated: 2023/11/24 16:51:41 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_info	ft_info_init(int flag, int argc, char **argv, char **envp)
{
	t_info	info;

	info.path_list = ft_envpath_split(envp);
	info.argc = argc;
	info.argv = argv;
	if (flag == 0)
	{
		info.infile_fd = open (argv[1], O_RDONLY);
		info.outfile_fd = open (argv[argc - 1],
				(O_WRONLY | O_TRUNC | O_CREAT), 0666);
		if (info.infile_fd == -1 || info.outfile_fd == -1)
			ft_errorout_file(info);
		info.heredoc_flag = 0;
	}
	else if (flag == 1)
	{
		info.infile_fd = open (".tmp_heredoc", O_RDONLY);
		info.outfile_fd = open (argv[argc - 1],
				(O_WRONLY | O_APPEND | O_CREAT), 0666);
		if (info.infile_fd == -1 || info.outfile_fd == -1)
			ft_errorout("open");
		info.heredoc_flag = 1;
	}
	return (info);
}
