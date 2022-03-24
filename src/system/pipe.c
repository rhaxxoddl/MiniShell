/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:26:10 by sanjeon           #+#    #+#             */
/*   Updated: 2022/03/24 21:32:20 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	ft_pipe(t_arg *arg, int cmd_idx)
{
	pid_t	pid;

	if (pipe(arg->fds[cmd_idx]) == -1)
		p_a_error(arg);
	connect_redir(arg->c_t[cmd_idx].redir, arg);
	pid = fork();
	if (pid == -1)
		p_a_error(arg);
	else if (pid == 0)
	{
		connect_pipe(cmd_idx, arg);
		if (execve(arg->c_t[cmd_idx].cmd[0], arg->c_t[arg->cmd_idx].cmd, arg->envp) == -1)
			p_a_error(arg);
	}
	if (pid)
	{
		close(arg->fds[cmd_idx][W]);
		dup2(arg->fds[cmd_idx][R], STDIN_FILENO);
		close(arg->fds[cmd_idx][R]);
		waitpid(pid, &(arg->status), 0);
	}
	return (0);
}

void	connect_pipe(int cmd_idx, t_arg *arg)
{
	if (cmd_idx != arg->cmd_count - 1)
	{
		if (dup2(arg->fds[cmd_idx][W], STDOUT_FILENO) == -1)
			p_a_error(arg);
		close(arg->fds[cmd_idx][W]);
		close(arg->fds[cmd_idx][R]);
	}
}

void	connect_redir(t_redir *redir, t_arg *arg)
{
	t_redir	*temp;

	temp = redir;
	while (temp != 0)
	{
		if (sellect_redir(temp) == 0)
			p_a_error(arg);
		temp = temp->next;
	}
}

int	sellect_redir(t_redir *redir)
{
	if (redir->redir_type == HERE_DOC)
	{
		if (redir_here_doc(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_IN)
	{
		if (redir_in(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_OUT)
	{
		if (redir_out(redir->filename) == -1)
			return (0);
	}
	else if (redir->redir_type == REDIR_APP)
	{
		if (redir_app(redir->filename) == -1)
			return (0);
	}
	return (1);
}
