/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/09 11:07:09 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_env(char *argv[], char *envp[])
{
	int	i;

	if (argv[1])
	{
		ft_putstr_fd("env: \'", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstrendl_fd("\' : No such file or directory", 2);
		return (1);
	}
	i = -1;
	while (envp[++i])
	{
		if (!ft_strchr(envp[i], '=') || envp[i][0] == '?')
			continue ;
		ft_putstrendl_fd(envp[i], 1);
	}
	return (0);
}
