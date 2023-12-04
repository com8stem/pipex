/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 21:01:28 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 21:59:17 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include "./libft/libft.h"

typedef struct s_info
{
	char	**argv;
	int		argc;
	int		infile_fd;
	int		outfile_fd;
	char	**path_list;
	int		heredoc_flag;
}	t_info;

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

int		ft_get_cmdpath(char **envp, char *path);
void	ft_exec(t_info info, int i);
char	**ft_envpath_split(char **envp);
char	*ft_check_path(t_info info, char *cmd);
char	*ft_cmdoption_init(char *cmd);
t_info	ft_info_init(int checkflag, int argc, char **argv, char **envp);
char	**ft_cmd_set(t_info info, char *str);
int		check_argv(int argc, char **argv);
char	*get_next_line(int fd);
int		write_heredoc(char **argv);
void	ft_errorout(char *errorname);
void	ft_errorout_file(t_info info);
void	ft_put_error_cmd(char *error, char *cmd, int index);
void	ft_put_error_cmd_without_free(char *error, char *cmd, int index);
void	ft_argc_error(char *error);

#endif