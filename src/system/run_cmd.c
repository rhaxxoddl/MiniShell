/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:26:10 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/26 10:42:10 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"

int	run_process(t_arg *arg, t_cmd_arg *cmd_arg)
{
	// print_arg(cmd_arg);
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == -1)
		p_a_error(arg);
	else if (pid == 0)
	{
		while (cmd_arg->cmd_head != 0)
		{
			if (run_cmd(arg, cmd_arg->cmd_head) != 0)
				p_a_error(arg);
			cmd_arg->cmd_head = cmd_arg->cmd_head->next;
		}
		exit(0);
	}
	else if (pid > 0)
		wait(&status);
	return (0);
}

int	run_cmd(t_arg *arg, t_cmd *cmd_head)// 새로운 프로세스이기 때문에 arg까지 해제하는 게 아니라 해제
{
	pid_t	pid;
	int		exit_process;

	exit_process = 0;
	if (pipe(arg->cmd_arg->fds[cmd_head->cmd_idx]) == -1)
		p_a_error(arg);
	connect_redir(cmd_head->redir, arg);
	pid = fork();
	if (pid == -1)
		p_a_error(arg);
	else if (pid == 0)
	{
		connect_pipe(cmd_head->cmd_idx, arg);
		cmd_head->cmd_param[0] = cmd_connect_path(cmd_head->cmd_param[0],
				arg->cmd_arg->path);
		if (execve(cmd_head->cmd_param[0],
				cmd_head->cmd_param, arg->envp) == -1)
			p_a_error(arg);
	}
	else if (pid > 0)
	{
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][W]);
		dup2(arg->cmd_arg->fds[cmd_head->cmd_idx][R], STDIN_FILENO);
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][R]);
		waitpid(pid, &(arg->status), 0);
	}
	return (0);
}

void	connect_pipe(int cmd_idx, t_arg *arg)
{
	if (cmd_idx != arg->cmd_arg->cmd_count - 1)
	{
		if (dup2(arg->cmd_arg->fds[cmd_idx][W], STDOUT_FILENO) == -1)
			p_a_error(arg);
		close(arg->cmd_arg->fds[cmd_idx][W]);
		close(arg->cmd_arg->fds[cmd_idx][R]);
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
