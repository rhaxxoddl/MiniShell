/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:12:47 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/25 20:24:43 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <limits.h>

int	ft_echo(char *argv[])
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!ft_strncmp(argv[i + 1], "-n", 2))
	{
		n = 1;
		i++;
	}
	while (argv[++i] != 0)
	{
		write(STDOUT_FILENO, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1] != 0)
			write(STDOUT_FILENO, " ", 1);
	}
	if (n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}

void	ft_exit(int	status)
{
	write(1, "exit\n", 5);
	exit(status);
}
