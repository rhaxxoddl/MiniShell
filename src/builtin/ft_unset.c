/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:34:33 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/02 21:39:38 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	_check_arg(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
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
		while (envp[i][++j] || str[j])
		{
			if (envp[i][j] != str[j] || envp[i][j] == '=')
				break ;
		}
		if (envp[i][j] == str[j] || (envp[i][j] == '=' && !str[j]))
			return (i);
	}
	return (-1);
}

static void	_unset(char *str, char **envp[])
{
	int	i;
	int	size;

	i = find_env(str, *envp);
	if (i >= 0)
	{
		free((*envp)[i]);
		size = -1;
		while ((*envp)[++size] != 0)
			;
		if (!size)
			return ;
		(*envp)[i] = (*envp)[size - 1];
		(*envp)[size - 1] = 0;
	}
}

int	ft_unset(char *argv[], char **envp[])
{
	int	i;
	int	status;

	if (!argv[1])
		return (0);
	i = 0;
	status = 0;
	while (argv[++i])
	{
		if (!_check_arg(argv[i]))
		{
			ft_putstr_fd("minishell: unset: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstrendl_fd("\': not a valid identifier", 2);
			status = 1;
		}
		else
			_unset(argv[i], envp);
	}
	return (status);
}
