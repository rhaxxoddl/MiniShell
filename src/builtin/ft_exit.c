/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinoh <jinoh@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:56:00 by jinoh             #+#    #+#             */
/*   Updated: 2022/04/24 15:35:33 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

long long check_atoll(char *str)
{
	long long sign;
	long long ret;

	ret = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && ((ret == 922337203685477580 && *str > '7')
		                  || (ret > 922337203685477580)))
			return (0);
		else if (sign == -1 && ((ret == -922337203685477580 && *str > '8')
		                        || (ret < -922337203685477580)))
			ret = ret * 10 + sign * (*str - '0');
		str++;
	}
	return (ret);
}

void	ft_exit(char *argv[])
{
	int argc;

	argc = 0;
	while (argv[argc] != NULL)
		++argc;
	if (argc == 1)
	{
		write(1, "exit", 4);
		exit(EXIT_SUCCESS);
	}
	if (argc == 2 && (!check_atoll(argv[2]) && ft_strlen(argv[2]) > 2))
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, argv[2], ft_strlen(argv[2]));
		write(2, ": numeric argument required", 27);
		exit(255);
	}
	else if (argc > 2)
	{
		write(2, "exit\nminishell: exit: too many arguments", 40);
		exit(EXIT_FAILURE);
	}
	write(1, "exit", 4);
	exit(check_atoll(argv[2]) % 256);
}