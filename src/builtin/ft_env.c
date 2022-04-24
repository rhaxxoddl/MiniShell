/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 18:31:19 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/24 19:31:21 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_env(char *argv[], char *envp[])
{
	int i;

	if (argv[0])
	{
		write(2, "env: ", 5);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, ": No such file or directory", 27);
		return ;
	}
	i = -1;
	while (envp[++i])
	{
		if (!ft_strchr(envp[i], '='))
			continue;
		write(1, envp[i], ft_strlen(envp[i]));
	}
}