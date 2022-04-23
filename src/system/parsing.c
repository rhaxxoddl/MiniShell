/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:40:49 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/23 13:44:47 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"

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
