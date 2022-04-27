/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 16:56:43 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/27 21:49:40 by sanjeon          ###   ########.fr       */
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
		printf("rl : %p\n", *rl);
		if (*rl == 0)
			return (comein_limitor(fd, str, rl));
		else
		{
			printf("str : %p", *str);
			*str = add_nl(str);
			if (*str == 0)
				return (0);
			if (*str != 0)
			{
				*str = here_app_str(str, rl);
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
	printf("exit while\n");
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
	printf("comein\n");
	// *str = add_nl(str);
	// if (*str == 0)
		// return (0);
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
	printf("is_limitor : %s\n", rl);
	return (rl);
}

char	*here_app_str(char **str, char **rl)
{
	// char	*temp1;
	char	*temp2;

	// temp1 = ft_strj oin(*str, "\n");
	// free(*str);
	// if (temp1 == 0)
	// 	return (0);
	// temp2 = ft_strjoin(temp1, *rl);
	temp2 = ft_strjoin(*str, *rl);
	// free_return(&temp1, rl, 0);
	free(*str);
	// temp1 = 0;
	if (temp2 == 0)
		return (0);
	return (temp2);
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
