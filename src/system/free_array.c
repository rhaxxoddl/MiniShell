/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:18:01 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/21 08:24:42 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <stdlib.h>

void	free_str_arr(char **str_arr)
{
	int	i;

	i = -1;
	while (str_arr[++i] != 0)
	{
		free(str_arr[i]);
		str_arr[i] = 0;
	}
	free(str_arr);
	str_arr = 0;
}

void	free_path(char **path)
{
	int	i;

	i = -1;
	while (path[++i] != 0)
	{
		free(path[i]);
		path[i] = 0;
	}
	free(path);
	path = 0;
}

void	free_fds(int **fds)
{
	int	i;

	i = -1;
	if (fds != 0)
	{
		while (fds[++i] != 0)
		{
			free(fds[i]);
			fds[i] = 0;
		}
		free(fds);
		fds = 0;
	}
}
