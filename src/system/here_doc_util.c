/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:56:43 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/25 16:58:29 by sanjeon          ###   ########.fr       */
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
		*rl = is_limitor(readline("heredoc> "), limitor);
		if (*rl == 0)
			return (comein_limitor(fd, str, rl));
		else
		{
			if (*str != 0)
			{
				*str = add_str(str, rl);
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

char	*is_limitor(char *str, const char *limitor)
{
	if ((ft_strlen(str) == ft_strlen(limitor))
		&& !ft_strncmp(str, limitor, ft_strlen(str)))
	{
		free(str);
		return (0);
	}
	return (str);
}

char	*add_str(char **str, char **rl)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(*str, *rl);
	free_return(str, rl, 0);
	if (temp1 == 0)
		return (0);
	temp2 = ft_strjoin(temp1, "\n");
	free(temp1);
	temp1 = 0;
	if (temp2 == 0)
		return (0);
	return (temp2);
}