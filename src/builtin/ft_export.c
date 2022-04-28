/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/28 19:31:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
//////////////////
void	ft_putstrendl_fd(char *s, int fd);

int check_arg(char *str)
{
	int i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[++i])
	{
		if (str[i] == '=')
			break;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	if (i == 1 && str[0] == '_')
		return (2);
	return (1);
}

static int find_env(char *str, char *envp[])
{
	int i;
	int j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] && str[j])
		{
			if (envp[i][j] != str[j] || envp[i][j] == '=' || str[j] == '=')
				break;
		}
		if (envp[i][j] == str[j] || (!envp[i][j] && str[j] == '='))
			return (i);
	}
	return (0);
}

static void    _export(char *str, char *envp[])
{
	int i;

	i = find_env(str, envp);
	if (i)
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
		if (!envp[i])
			exit(EXIT_FAILURE);
	}
	else
	{
		i = ft_strlen(envp[]);
		envp[i] = ft_strdup(str);
		envp[i + 1] = 0;
		if (!envp[i])
			exit(EXIT_FAULRE);
	}
}

void	ft_export(char *argv[], char *envp[])
{
	int i;
	int chk;

	if (!argv[1])
		print_envp(envp);
	i = 0;
	while (argv[++i])
	{
		chk = check_arg(argv[i]);
		if (!chk)
		{
			ft_putstr_fd("minishell: export: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstrendl_fd("\': not a valid identifier", 2);
		}
		else if (chk == 2)
			;
		else
			_export(argv[i], envp);
	}
}