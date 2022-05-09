/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:56:00 by jinoh             #+#    #+#             */
/*   Updated: 2022/05/02 21:38:39 by jinoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "builtin.h"

static int	_check_atoll(char *str)
{
	long long	sign;
	long long	ret;

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
			return (0);
		ret = ret * 10 + sign * (*str - '0');
		str++;
	}
	return (1);
}

static long long	_ft_atoll(char *str)
{
	long long	sign;
	long long	ret;

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
		ret = ret * 10 + sign * (*str - '0');
		str++;
	}
	return (ret);
}

static int	_isnum(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0')
		return (0);
	return (1);
}

void	ft_exit(char *argv[])
{
	int	argc;

	argc = 0;
	while (argv[argc] != NULL)
		++argc;
	if (argc == 1)
	{
		ft_putstrendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
	else if (!_isnum(argv[1]) || !_check_atoll(argv[1]))
	{
		ft_putstr_fd("exit\nminishell: exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstrendl_fd(": numeric argument required", 2);
		exit(255);
	}
	else if (argc > 2)
	{
		ft_putstrendl_fd("exit\nminishell: exit: too many arguments", 2);
		exit(EXIT_FAILURE);
	}
	ft_putstrendl_fd("exit", 1);
	exit(_ft_atoll(argv[1]) % 256);
}
