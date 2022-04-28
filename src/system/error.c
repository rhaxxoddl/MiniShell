/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:42:15 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 09:03:31 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <errno.h>
#include <stdio.h>

/*
A temporary function of the function
that releases the arg you created.
*/
void	free_arg(t_arg *arg)
{
	(void)arg;
	return ;
}

void	p_a_error(t_arg *arg)
{
	free_arg(arg);
	perror("minishell");
	printf("errno : %d\n", errno);
	exit(errno);
}

void	cnf_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}
