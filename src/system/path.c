/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 12:47:30 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/21 08:55:29 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	**get_path(char *envp[])
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	path = ft_split_p((char *)(envp[i] + 5), ':');
	if (path == 0)
		return (0);
	i = 0;
	while (path[i] != 0)
		i++;
	path[i] = add_pwd(envp);
	if (path[i] == 0)
	{
		free_path(path);
		return (0);
	}
	if (add_slash(path) == -1)
		return (0);
	return (path);
}

char	*add_pwd(char *envp[])
{
	int		i;
	char	*pwd;

	i = 0;
	while (ft_strncmp(envp[i], "PWD=", 4) != 0)
		i++;
	pwd = ft_strdup((char *)(envp[i] + 4));
	if (pwd == 0)
		return (0);
	return (pwd);
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
			free_path(path);
			return (-1);
		}
		free(path[i]);
		path[i] = temp;
	}
	return (1);
}
