/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:56:43 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/09 19:48:18 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdlib.h>

int	until_comein_limitor(const char *limitor, int fd)
{
	char	*str;
	char	*rl;

	str = 0;
	rl = 0;
	while (1)
	{
		rl = is_limitor(readline("> "), limitor);
		if (rl == 0)
			return (comein_limitor(fd, &str, &rl));
		else
		{
			if (str != 0)
				str = here_app_str(&str, &rl);
			else
			{
				str = ft_strdup(rl);
				if (str == 0)
					ft_error();
			}
			rl = 0;
		}
	}
	return (0);
}

int	comein_limitor(int fd, char **str, char **rl)
{
	*str = add_nl(str);
	ft_putstr_fd(*str, fd);
	close(fd);
	fd = open("temp", O_RDONLY);
	if (dup2(fd, STDIN_FILENO) == -1)
		ft_error();
	close(fd);
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
