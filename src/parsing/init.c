/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:20 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/29 09:51:00 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char **copy_envp(char *envp[])
{
	char **ret;
	int size;
	int i;

	size = -1;
	while (envp[++size])
		;
	ret = malloc((size + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		ret[i] = ft_strdup(envp[i]);
	ret[i] = 0;
	return (ret);
}

t_arg	*init_arg(char **envp)
{
	t_arg	*arg;

	arg = (t_arg *)ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		return (0);
	// arg->env = init_env(envp);
	arg->envp = copy_envp(envp);
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
				return("error");
			return (output);
		}
		free(env_key);
		i++;
	}
	return (0);
}
