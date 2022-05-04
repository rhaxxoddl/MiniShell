/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:56:43 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/04 20:16:21 by sanjeon          ###   ########.fr       */
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
				*str = here_app_str(str, rl);
				if (*str == 0)
					ft_error();
			}
			else
			{
				*str = ft_strdup(*rl);
				if (*str == 0)
					ft_error();
			}
			*rl = 0;
		}
	}
	return (0);
}

int	comein_limitor(int fd, char **str, char **rl)
{
	*str = add_nl(str);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error();
	close(fd);
	write(STDIN_FILENO, *str, ft_strlen(*str));
	fd = open("temp", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error();
	if (unlink("temp") == -1)
		ft_error();
	free(*str);
	free(*rl);
	return (1);
}

char	*is_limitor(char *rl, const char *limitor)
{
	if (rl != 0 && (ft_strlen(rl) == ft_strlen(limitor))
		&& !ft_strncmp(rl, limitor, ft_strlen(rl)))
	{
		free(rl);
		return (0);
	}
	return (rl);
}

char	*here_app_str(char **str, char **rl)
{
	char	*temp;

	*str = add_nl(str);
	temp = ft_strjoin(*str, *rl);
	if (temp == 0)
		ft_error();
	free(*str);
	free(*rl);
	return (temp);
}

char	*add_nl(char **str)
{
	char	*temp;

	temp = ft_strjoin(*str, "\n");
	if (temp == 0)
		ft_error();
	free(*str);
	return (temp);
}
