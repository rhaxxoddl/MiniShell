/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:56:43 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 07:38:29 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int	until_comein_limitor(char **str, char **rl, const char *limitor, int fd)
{
	while (1)
	{
		*rl = is_limitor(readline("> "), limitor);
		if (*rl == 0)
			return (comein_limitor(fd, str, rl));
		else
		{
			if (*str != 0)
			{
				*str = here_add_str(str, rl);
				if (*str == 0)
					return (0);
			}
			else
			{
				*str = ft_strdup(*rl);
				if (*str == 0)
					return (free_return(str, rl, 0));
			}
			free(*rl);
			*rl = 0;
		}
	}
	return (0);
}

int	free_return(char **str, char **rl, int status)
{
	if (*str != 0)
	{
		free(*str);
		*str = 0;
	}
	if (*rl != 0)
	{
		free(*rl);
		*rl = 0;
	}
	return (status);
}

int	comein_limitor(int fd, char **str, char **rl)
{
	*str = add_nl(str);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (free_return(str, rl, 0));
	close(fd);
	write(STDIN_FILENO, *str, ft_strlen(*str));
	fd = open("temp", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (free_return(str, rl, 0));
	if (unlink("temp") == -1)
		return (free_return(str, rl, 0));
	return (free_return(str, rl, 1));
}

char	*is_limitor(char *rl, const char *limitor)
{
	if ((ft_strlen(rl) == ft_strlen(limitor))
		&& !ft_strncmp(rl, limitor, ft_strlen(rl)))
	{
		free(rl);
		return (0);
	}
	return (rl);
}

char	*here_add_str(char **str, char **rl)
{
	char	*temp;

	*str = add_nl(str);
	if (*str == 0)
		return (0);
	temp = ft_strjoin(*str, *rl);
	free_return(&(*str), rl, 0);
	if (temp == 0)
		return (0);
	return (temp);
}

char	*add_nl(char **str)
{
	char	*temp;

	temp = ft_strjoin(*str, "\n");
	if (temp == 0)
		return (0);
	free(*str);
	return (temp);
}
