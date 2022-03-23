/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:59:13 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/23 11:04:22 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <fcntl.h>
#include <readline/history.h>

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

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND);
	if (fd < 0)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (-1);
	return (1);
}

int	here_doc(char *limitor)
{
	char	*str;
	char	*temp;
	char	*rl;
	int		i;

	temp = 0;
	str = 0;
	rl = 0;
	i = 0;
	while (1)
	{
		rl = is_limitor(readline("heredoc"), limitor);
		if (rl == 0)
			
	}
}

char	*is_limitor(char *str, char *limitor)
{
	if ((ft_strlen(str) == ft_strlen(limitor)) && ft_strncmp(str, limitor, ft_strlen(str)))
		return (str);
	return (0);
}

char	*trans_env_in_str(char *str, char **envp)
{
	
}
