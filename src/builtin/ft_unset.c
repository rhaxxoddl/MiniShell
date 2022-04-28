/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:34:33 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/28 18:01:02 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
///////////////
void	ft_putstrendl_fd(char *s, int fd);

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
			ft_putstr_fd("minishell: unset: \'", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstrendl_fd("\': not a valid identifier", 2);
		}
		else
			_unset(argv[i], envp);
	}
}