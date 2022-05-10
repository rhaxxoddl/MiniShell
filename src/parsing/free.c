/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 17:09:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 08:55:36 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

void	free_str_arr(char **str_arr)
{
	int	i;

	i = -1;
	if (str_arr == NULL)
		return ;
	while (str_arr[++i] != NULL)
	{
		free(str_arr[i]);
		str_arr[i] = 0;
	}
	str_arr = 0;
}

void	free_reidr(t_redir *redir)
{
	t_redir	*temp;

	while (redir != NULL)
	{
		if (redir->filename != NULL)
			free(redir->filename);
		temp = redir;
		redir = redir->next;
		free(temp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd != NULL)
	{
		free_str_arr(cmd->cmd_p);
		free(cmd->cmd_p);
		free_reidr(cmd->redir);
		temp = cmd;
		cmd = cmd->next;
		free(temp);
	}
}

void	free_fds(int **fds)
{
	int	i;

	if (fds == NULL)
		return ;
	i = -1;
	while (fds[++i] != NULL)
		free(fds[i]);
	free(fds);
}

void	free_cmd_arg(t_cmd_arg *cmd_arg)
{
	if (cmd_arg == NULL)
		return ;
	free_str_arr(cmd_arg->path);
	free(cmd_arg->path);
	free_cmd(cmd_arg->cmd_head);
	free_fds(cmd_arg->fds);
	free(cmd_arg);
}
