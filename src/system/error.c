/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:42:15 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/25 13:00:39 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"
#include <errno.h>
#include <stdio.h>

void	free_arg(t_arg *arg)
{
	(void)arg;
	return ;
}

void	p_a_error(t_arg *arg)
{
	free_arg(arg);
	perror("Error");
	printf("errno : %d\n", errno);
	exit(errno);
}
