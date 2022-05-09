/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/09 11:04:44 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin.h"

static int	_check_arg(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (str[i] == '=')
			break ;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	if (i == 1 && str[0] == '_')
		return (2);
	return (1);
}

static int	find_env(char *str, char *envp[])
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] && str[j])
		{
			if (envp[i][j] != str[j] || envp[i][j] == '=' || str[j] == '=')
				break ;
		}
		if (envp[i][j] == str[j] || (!envp[i][j] && str[j] == '='))
			return (i);
	}
	return (-1);
}

static char	**append_envp(char **envp[], char *str)
{
	int		size;
	int		i;
	char	**ret;

	size = -1;
	while ((*envp)[++size])
		;
	ret = ft_calloc(size + 2, sizeof(char *));
	if (!ret)
		exit(EXIT_FAILURE);
	i = -1;
	while (++i < size)
		ret[i] = (*envp)[i];
	ret[i] = ft_strdup(str);
	if (!ret[i])
		exit(EXIT_FAILURE);
	free(*envp);
	return (ret);
}

void	update_env(char *str, char **envp[])
{
	int	i;

	i = find_env(str, *envp);
	if (i >= 0)
	{
		free((*envp)[i]);
		(*envp)[i] = ft_strdup(str);
		if (!(*envp)[i])
			exit(EXIT_FAILURE);
	}
	else
		*envp = append_envp(envp, str);
}

int	ft_export(char *argv[], char **envp[])
{
	int	i;
	int	chk;
	int	status;

	if (!argv[1])
		print_envp(*envp);
	i = 0;
	status = 0;
	while (argv[++i])
	{
		chk = _check_arg(argv[i]);
		if (!chk)
		{
			ft_putstr_fd("minishell: export: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstrendl_fd("\': not a valid identifier", 2);
			status = 1;
		}
		else if (chk == 2)
			;
		else
			update_env(argv[i], envp);
	}
	return (status);
}
