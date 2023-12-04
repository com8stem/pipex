/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd_name.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:42:43 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/04 22:00:10 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_get_cmdpath(char **envp, char *path)
{
	int	path_index;

	path_index = 0;
	while (envp[path_index] != NULL)
	{
		if (ft_strnstr(envp[path_index], path, ft_strlen(path)) != NULL)
			return (path_index);
		path_index++;
	}
	ft_argc_error("PATH not found");
	return (-1);
}

char	**ft_envpath_split(char **envp)
{
	char	*path_start;
	char	**path_list;

	path_start = envp[ft_get_cmdpath(envp, "PATH=")] + ft_strlen("PATH=");
	path_list = ft_split(path_start, ':');
	return (path_list);
}

char	*ft_check_path(t_info info, char *cmd)
{
	char	*cmd_path;
	int		i;

	i = 0;
	if (cmd != NULL && (cmd[0] == '/' || cmd[0] == '.'))
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		ft_put_error_cmd(": no such file or directory: ", cmd, 0);
	}
	else if (cmd != NULL)
	{
		cmd = ft_strjoin("/", cmd);
		while (info.path_list[i++] != NULL)
		{
			cmd_path = ft_strjoin(info.path_list[i], cmd);
			if (access(cmd_path, X_OK) == 0)
				return (cmd_path);
			free(cmd_path);
		}
		ft_put_error_cmd(": command not found: ", cmd, 1);
	}
	ft_put_error_cmd(": command not found: ", cmd, 0);
	return (NULL);
}

int	ft_allspace(char *str)
{
	if (str == NULL)
		return (-1);
	while (*str != '\0')
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

char	**ft_cmd_set(t_info info, char *str)
{
	char	**cmd;

	if (ft_allspace(str))
		ft_put_error_cmd_without_free(": command not found: ", str, 0);
	cmd = ft_split(str, ' ');
	if (cmd == NULL)
		return (NULL);
	cmd[0] = ft_check_path(info, cmd[0]);
	return (cmd);
}
