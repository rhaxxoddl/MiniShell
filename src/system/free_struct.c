/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:18:18 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/22 20:56:47 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <stdlib.h>

void	free_arg(t_arg *arg)
{
	int	i;

	i = -1;
	if (arg != 0)
	{
		if (arg->cmd_list != 0)
			clear_cmd_list(arg->cmd_list);
		free_fds(arg->fds);
		if (arg->infile != 0)
			free(arg->infile);
		arg->infile = 0;
		if (arg->outfile != 0)
			free(arg->outfile);
		arg->outfile = 0;
		free_path(arg->path);
		free(arg->limitor);
		arg->limitor = 0;
		free(arg);
		arg = 0;
	}
}

void	clear_cmd_list(t_cmd_list *head)
{
	t_cmd_list	*temp;
	t_cmd_list	*after;

	temp = head;
	while (temp != 0)
	{
		after = temp->next;
		free_cmd_list(temp);
		temp = after;
	}
}

void	free_cmd_list(t_cmd_list *dest)
{
	free(dest->cmd);
	free_str_arr(dest->cmd_with_option);
	free(dest->cmd_path);
	free(dest);
}
