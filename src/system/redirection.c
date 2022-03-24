/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 13:59:13 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/24 21:37:23 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <fcntl.h>
#include <readline/readline.h>
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
	printf("redir_out\n");
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

int	redir_here_doc(const char *limitor)
{
	int		fd;
	char	*str;
	char	*temp;
	char	*rl;
	int		i;

	temp = 0;
	str = 0;
	rl = 0;
	i = 0;
	fd = open("temp", O_WRONLY | O_CREAT, 0755);
	if (fd < 0)
		return (-1);
	// grep에 fd를 넘겨줘야 함.
	while (1)
	{

		rl = is_limitor(readline("heredoc> "), limitor);
		if (rl == 0)
		{
			if (dup2(fd, STDIN_FILENO) == -1)
				return (-1);
			close(fd);
		// if (unlink("temp") == -1)
		// 	return (-1);
			write(STDIN_FILENO, str, ft_strlen(str));
			close(STDIN_FILENO);
			break;
		}
		else
			rl = add_str(rl, "\n");
		if (rl == 0 && str != 0)
		{
			free(str);
			return (0);
		}
		if (str == 0)
			str = ft_strdup(rl);
		else
		{
			temp = ft_strjoin(str, rl);
			if (temp == 0)
			{
				if (str != 0)
					free(str);
				return (0);
			}
			free(str);
			str = temp;
			rl = 0;
		}
	}
	return (1);
}

char	*is_limitor(char *str, const char *limitor)
{
	if ((ft_strlen(str) == ft_strlen(limitor)) && !ft_strncmp(str, limitor, ft_strlen(str)))
		return (0);
	return (str);
}

char	*add_str(char *str, char *add)
{
	char	*temp;
	
	temp = ft_strjoin(str, add);
	if (temp == 0)
		return (0);
	return (temp);
}
