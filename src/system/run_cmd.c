/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:26:10 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/19 10:27:26 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"

int	run_cmd(t_arg *arg, int cmd_idx)
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
		if (execve(arg->c_t[cmd_idx].cmd_param[0], arg->c_t[arg->cmd_idx].cmd_param,
				arg->envp) == -1)
			p_a_error(arg);
	}
	if (pid)
	{
		close(arg->fds[cmd_idx][W]);
		dup2(arg->fds[cmd_idx][R], STDIN_FILENO);
		close(arg->fds[cmd_idx][R]);
		waitpid(pid, &(arg->status), WNOHANG);
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
		if (redir_here(redir->filename) == -1)
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
