/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: goosterl <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/21 15:12:54 by goosterl      #+#    #+#                 */
/*   Updated: 2020/01/23 16:29:06 by goosterl      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_checkbuf(char *tmp)
{
	if (tmp)
	{
		if (ft_strlen_nl(tmp) >= 0)
			return (1);
	}
	return (0);
}

int		gnl_make_temp(char **tmp, char *buf)
{
	char	*ptr;

	ptr = NULL;
	if (buf == NULL)
		return (GNL_ERROR);
	if (*tmp)
		ptr = ft_strjoin(*tmp, buf);
	else
		ptr = ft_strndup(buf, ft_strlen_c(buf, '\0'));
	if (ptr == NULL)
		return (GNL_ERROR);
	free(*tmp);
	*tmp = ptr;
	return (GNL_EOF);
}

int		gnl_make(char **line, char **tmp, char c)
{
	t_ldata		data;

	data.str = NULL;
	if (*tmp == NULL)
		return (GNL_ERROR);
	data.plen = 0;
	data.len = ft_strlen_c(*tmp, c);
	data.str = ft_strndup(*tmp, data.len);
	if (data.str == NULL)
		return (GNL_ERROR);
	data.plen = ft_strlen_c(*tmp, '\0');
	if (data.len + 1 < data.plen)
		ft_memcpy(*tmp, (*tmp + data.len + 1), (data.plen - data.len));
	else
	{
		free(*tmp);
		*tmp = NULL;
	}
	*line = data.str;
	return (c == '\n' ? GNL_READ : GNL_EOF);
}

int		get_next_line(int fd, char **line)
{
	t_data			data;
	static char		*tmp[1024];

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (GNL_ERROR);
	if (gnl_checkbuf(tmp[fd]))
		return (gnl_make(line, &tmp[fd], '\n'));
	else
		data.ret = read(fd, data.buf, BUFFER_SIZE);
	if (data.ret <= 0 && tmp[fd] == NULL)
	{
		if (data.ret == 0)
			*line = ft_strndup("", 1);
		return (data.ret == 0 ? GNL_EOF : GNL_ERROR);
	}
	data.buf[data.ret] = '\0';
	if (gnl_make_temp(&tmp[fd], data.buf) == GNL_ERROR)
		return (GNL_ERROR);
	if (data.ret == 0)
		return (gnl_make(line, &tmp[fd], '\0'));
	else if (ft_strlen_nl(tmp[fd]) >= 0)
		return (gnl_make(line, &tmp[fd], '\n'));
	else
		return (get_next_line(fd, line));
}
