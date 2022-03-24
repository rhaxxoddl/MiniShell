/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:40:49 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/24 11:19:04 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

t_arg	*init_arg(void)
{
	t_arg	*arg;

	arg = 0;
	arg = ft_calloc(1, sizeof(t_arg));
	if (arg == 0)
		p_a_error(arg);
	arg->c_t = 0;
	arg->cmd_count = 0;
	arg->cmd_idx = 0;
	arg->fds = 0;
	arg->status = 0;
	arg->envp = 0;
	return (arg);
}

int	**malloc_fds(int cmd_count)
{
	int	**fds;
	int	i;

	fds = (int **)ft_calloc(cmd_count + 1, sizeof(int *));
	if (fds == 0)
		return (0);
	i = -1;
	while (++i < cmd_count)
	{
		fds[i] = (int *)ft_calloc(2, sizeof(int));
		// if (fds[i] == 0)
		// {
		// 	free_fds(fds);
		// 	return (0);
		// }
	}
	return (fds);
}
