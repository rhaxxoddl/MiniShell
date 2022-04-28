/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/28 16:56:54 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
////////////////////
void	ft_putstrendl_fd(char *s, int fd);

void	ft_env(char *argv[], char *envp[])
{
	int i;

	if (argv[1])
	{
		ft_putstr_fd("env: \'", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstrendl_fd("\' : No such file or directory", 2);
		return ;
	}
	i = -1;
	while (envp[++i])
	{
		if (!ft_strchr(envp[i], '='))
			continue;
		ft_putstrendl_fd(envp[i], 1);
	}
}