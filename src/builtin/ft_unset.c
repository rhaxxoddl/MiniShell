/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:34:33 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/24 19:34:53 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int check_arg(char *str)
{
	int i;

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

static int find_env(char *str, char *envp[])
{
	int i;
	int j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] || str[j])
		{
			if (envp[i][j] != str[j] || envp[i][j] == '=')
				break;
		}
		if (envp[i][j] == str[j] || (envp[i][j] =='=' && !str[j]))
			return (i);
	}
	return (0);
}

static void _unset(char *str, char *envp[])
{
	int i;
	int j;

	i = find_env(str, envp);
	if (i)
	{
		free(envp[i]);
		j = ft_strlen(envp[]);
		envp[i] = envp[j];
		envp[j] = 0;
	}
}

void	ft_unset(char *argv[], char *envp[])
{
	int i;

	if (!argv[1])
		return ;
	while (argv[++i])
	{
		if (!check_arg(argv[i]))
		{
			write(2, "-minishell: unset: \'", 20);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "\': not a valid identifier\n", 26);
		}
		else
			_unset(argv[i], envp);
	}
}