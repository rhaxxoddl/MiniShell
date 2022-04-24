/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 17:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/24 17:31:21 by jinoh            ###   ########.fr       */
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
		if (str[i] == '=')
			break;
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '_')
			return (0);
	}
	if (i == 1 && str[0] == '_')
		return (2);
	return (1);
}

int revise(char *str, char *envp[])
{
	int i;
	int j;

	i = -1;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] || str[j])
		{
			if (envp[i][j] != str[j] || envp[i][j] == '=' || str[j] == '=')
				break;
		}
		if (envp[i][j] == str[j] || (!envp[i][j] && str[j] == '='))
			return (i);
	}
	return (0);
}

void    _export(char *str, char *envp[])
{
	int i;

	i = revise(str, envp);
	if (i)
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
		if (!envp[i])
			exit(EXIT_FAILURE);
	}
	else
	{
		i = ft_strlen(envp);
		envp[i] = ft_strdup(str);
		envp[i + 1] = 0;
		if (!envp[i])
			exit(EXIT_FAULRE);
	}
}

void print_envp(char *envp[])
{
	int i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i][0] == '?')
			continue;
		write(1, "declare -x ", 11);
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
	}
}

void	ft_export(char *argv[], char *envp[])
{
	int i;

	if (!argv[1])
		print_envp(envp);
	i = 0;
	while (argv[++i])
	{
		if (!check_arg(argv[i]))
		{
			write(2, "-minishell: export: \'", 21);
			write(2, argv[i], ft_strlen(argv[i]));
			write(2, "\': not a valid identifier\n", 26);
		}
		else if (check_arg(argv[i]) == 2)
			return ;
		else
			_export(argv[i], envp);
	}
}