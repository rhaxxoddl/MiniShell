/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:40:49 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 12:21:17 by sanjeon          ###   ########.fr       */
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
		fds[i] = (int *)ft_calloc(3, sizeof(int));
		if (fds[i] == 0)
			perror("");
	}
	return (fds);
}
