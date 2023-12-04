/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:25:54 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 21:55:09 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_heredoc(char **argv)
{
	char	*oneline;
	int		tmp_fd;

	tmp_fd = open(".tmp_heredoc", (O_WRONLY | O_CREAT), 0666);
	if (tmp_fd == -1)
		ft_errorout("open");
	while (1)
	{
		write (STDOUT_FILENO, "> ", 2);
		oneline = get_next_line(STDIN_FILENO);
		if (oneline == NULL
			|| (((ft_strncmp(oneline, argv[2], ft_strlen(argv[2])) == 0))
				&& (oneline[ft_strlen(argv[2])] == '\n')))
			break ;
		if (oneline != NULL)
			write (tmp_fd, oneline, ft_strlen(oneline));
	}
	close (tmp_fd);
	return (3);
}
