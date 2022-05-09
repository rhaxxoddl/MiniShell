/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:59:20 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/09 20:43:46 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	**get_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;

	i = 0;
	temp = get_env(envp, "PATH");
	if (temp == 0)
		return (0);
	path = ft_split(temp, ':');
	free(temp);
	if (path == 0)
		return (0);
	if (path[i] == 0)
	{
		free_str_arr(path);
		return (0);
	}
	if (add_slash(path) == -1)
		return (0);
	return (path);
}

int	add_slash(char **path)
{
	int		i;
	char	*temp;

	i = -1;
	while (path[++i] != 0)
	{
		temp = ft_strjoin(path[i], "/");
		if (temp == 0)
		{
			free_str_arr(path);
			return (-1);
		}
		free(path[i]);
		path[i] = temp;
	}
	return (1);
}

char	*cmd_connect_path(char *cmd, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	temp = 0;
	while (path != 0 && path[i] != 0)
	{
		temp = ft_strjoin(path[i], cmd);
		if (temp == 0)
			return (0);
		if (access(temp, X_OK) == 0)
			return (temp);
		free(temp);
		temp = 0;
		i++;
	}
	temp = ft_strdup(cmd);
	if (temp == 0)
		return (0);
	if (access(temp, X_OK) != 0)
		cnf_error(cmd);
	return (temp);
}

int	**malloc_fds(int cmd_count)
{
	int	**fds;
	int	i;

	fds = (int **)ft_calloc(cmd_count + 1, sizeof(int *));
	if (fds == 0)
		return (0);
	i = -1;
	while (++i < cmd_count)
	{
		fds[i] = (int *)ft_calloc(3, sizeof(int));
		if (fds[i] == 0)
			perror("");
	}
	return (fds);
}
