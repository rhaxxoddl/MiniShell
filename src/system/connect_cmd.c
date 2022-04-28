/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:59:20 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 10:22:27 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "run_cmd.h"
//TODO : PATH를 처음에 가지고 다니는 게 아니라 명령어를 파싱할 때마다 가져오도록
char	**get_path(t_env *env_head)
{
	char	**path;
	int		i;

	i = 0;
	path = ft_split(get_env(env_head, "PATH"), ':');
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
	while (path[i] != 0)
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