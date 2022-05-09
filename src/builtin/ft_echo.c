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

#include "builtin.h"

int	ft_echo(char *argv[])
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (argv[1] != 0 && !ft_strcmp(argv[1], "-n"))
	{
		n = 1;
		i++;
	}
	while (argv[++i] != 0)
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1] != 0)
			ft_putstr_fd(" ", 1);
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
