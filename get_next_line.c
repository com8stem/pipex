/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kishizu <kishizu@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:28:58 by kishizu           #+#    #+#             */
/*   Updated: 2023/12/01 21:11:20 by kishizu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*free_return_note(char *buf, char *note)
{
	free (buf);
	return (note);
}

static char	*copy_to_note(int fd, char *note)
{
	char	*buf;
	int		read_bytes;
	char	*tmp;
	int		d_flag;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	d_flag = 0;
	while (1)
	{
		if (ft_strchr(note, '\n') != NULL)
			break ;
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
			ft_errorout("read");
		if (read_bytes == 0 && d_flag == 0)
			break ;
		buf[read_bytes] = '\0';
		tmp = note;
		note = ft_strjoin(note, buf);
		free(tmp);
		d_flag++;
	}
	return (free_return_note(buf, note));
}

static void	*ft_free_static(char *ptr)
{
	char	*tmp;

	tmp = ptr;
	ptr = NULL;
	free(tmp);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*note;
	char		*result;
	char		*tmp;
	size_t		result_len;

	if (fd < 0 || OPEN_MAX < fd || BUFFER_SIZE <= 0
		|| BUFFER_SIZE > SIZE_T_MAX - 1)
		return (NULL);
	note = copy_to_note(fd, note);
	if (note == NULL)
		return (NULL);
	if (ft_strchr(note, '\n') == NULL)
		result_len = ft_strlen(note);
	else
		result_len = ft_strchr(note, '\n') - note + 1;
	if (result_len == 0)
		return (NULL);
	result = ft_substr(note, 0, result_len);
	if (result == NULL)
		return (ft_free_static(note));
	tmp = note;
	note = ft_substr(note, result_len, ft_strlen(note) - result_len);
	free(tmp);
	return (result);
}
