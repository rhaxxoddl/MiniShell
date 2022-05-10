/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:20 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 08:55:36 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "builtin.h"

static char	**copy_envp(char *envp[])
{
	char	**ret;
	int		size;
	int		i;

	size = -1;
	while (envp[++size])
		;
	ret = ft_calloc(sizeof(char *), (size + 1));
	if (!ret)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < size)
	{
		ret[i] = ft_strdup(envp[i]);
		if (!ret[i])
		{
			size = i;
			i = -1;
			while (++i < size)
				free(ret[i]);
			exit(EXIT_FAILURE);
		}
	}
	ret[i] = 0;
	return (ret);
}

t_arg	*init_arg(char **envp)
{
	t_arg	*arg;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	arg->envp = copy_envp(envp);
	update_env("?=1", &(arg->envp));
	return (arg);
}

char	*get_env(char **envp, char *key)
{
	char	*output;
	char	*env_key;
	int		i;

	i = 0;
	while (envp[i] != 0)
	{
		env_key = ft_substr(envp[i], 0, find_end(envp[i]));
		if (ft_strcmp(env_key, key) == 0)
		{
			free(env_key);
			output = ft_strdup(&(envp[i][find_end(envp[i]) + 1]));
			if (output == 0)
				ft_error();
			return (output);
		}
		free(env_key);
		i++;
	}
	return (0);
}

t_cmd	*init_cmd(char **line)
{
	t_cmd	*cmd;

	while (ft_isspace(**line))
		(*line)++;
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (cmd == 0)
		ft_error();
	cmd->redir = 0;
	cmd->cmd_p = (char **)ft_calloc(1, sizeof(char *));
	if (cmd->cmd_p == 0)
		ft_error();
	return (cmd);
}
