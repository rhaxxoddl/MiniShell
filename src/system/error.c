/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:42:15 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 09:38:10 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <errno.h>
#include <stdio.h>

void	ft_error()
{
	printf("ft_error\n");
	perror("minishell");
	printf("errno : %d\n", errno);
	exit(errno);
}

void	cnf_error(char *cmd)
{
	printf("cnf_error\n");
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
