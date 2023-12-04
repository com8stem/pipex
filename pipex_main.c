/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:01:09 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 21:56:33 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// __attribute__((destructor))
// static void destructor() {
//     system("leaks -q pipex");
// }

int	check_argv(int argc, char **argv)
{
	if (argc < 5)
		return (-1);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc") + 1) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		checkflag;
	int		i;
	int		wait_count;
	int		wait_status;

	i = 2;
	checkflag = check_argv(argc, argv);
	if (checkflag == -1)
		ft_argc_error("Too few arguments!");
	if (checkflag == 1)
		i = write_heredoc(argv);
	info = ft_info_init(checkflag, argc, argv, envp);
	wait_count = i;
	while (i + 1 < argc)
		ft_exec(info, i++);
	while (wait_count++ < argc - 1)
		wait (&wait_status);
	if (WEXITSTATUS(wait_status))
		if (checkflag == 1)
			unlink(".tmp_heredoc");
	return (0);
}
