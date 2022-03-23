/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 11:42:15 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:56:56 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <errno.h>
#include <stdio.h>

void	p_a_error(t_arg *arg)
{
	free_arg(arg);
	perror("Error");
	exit(errno);
}
