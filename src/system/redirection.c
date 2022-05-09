/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:59:13 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/09 19:50:16 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>

int	sellect_redir(t_redir *redir, int *out)
{
	if (redir->redir_type == HERE_DOC)
	{
		if (redir_here(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_IN)
	{
		if (redir_in(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_OUT)
	{
		*out = 1;
		if (redir_out(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_APP)
	{
		*out = 1;
		if (redir_app(redir->filename) == -1)
			return (0);
	}
	return (1);
}

int	redir_in(const char *filename)
{
	int	fd;

	if (access(filename, R_OK) == -1)
		return (-1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (1);
}

int	redir_out(const char *filename)
{
	int	fd;

	fd = open(filename,
			O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (1);
}

int	redir_app(const char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	return (1);
}

int	redir_here(const char *limitor)
{
	int		fd;

	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC,
			S_IRWXU | S_IRWXG | S_IRWXO);
	if (fd < 0)
		return (0);
	return (until_comein_limitor(limitor, fd));
}
