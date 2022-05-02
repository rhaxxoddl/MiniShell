/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:26:10 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/02 19:54:58 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run_cmd.h"

int	run_process(t_arg *arg, t_cmd_arg *cmd_arg)
{
	pid_t	pid;

	if (ft_strncmp("exit", cmd_arg->cmd_head->cmd_param[0], 4) == 0) //cmd가 1개일 때 조건 추가
		ft_exit(cmd_arg->cmd_head->cmd_param);
	pid = fork();
	if (pid == -1)
		ft_error();
	else if (pid == 0)
	{
		while (cmd_arg->cmd_head != 0)
		{
			run_cmd(arg, cmd_arg->cmd_head);
			cmd_arg->cmd_head = cmd_arg->cmd_head->next;
		}
		if (WIFEXITED(arg->status))
			exit(WEXITSTATUS(arg->status));
		else if (WIFSIGNALED(arg->status))
			exit(WTERMSIG(arg->status));
	}
	else if (pid > 0)
	{
		waitpid(pid ,&(arg->status), 0);
		free_cmd_arg(cmd_arg);
	}
	return (0);
}

void	run_cmd(t_arg *arg, t_cmd *cmd_head)
{
	pid_t	pid;

	if (pipe(arg->cmd_arg->fds[cmd_head->cmd_idx]) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	else if (pid == 0)
	{
		connect_pipe(cmd_head->cmd_idx, arg);
		connect_redir(cmd_head->redir);
		exec_cmd(cmd_head->cmd_param, arg->envp, arg->cmd_arg->path);
	}
	else if (pid > 0)
	{
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][W]);
		dup2(arg->cmd_arg->fds[cmd_head->cmd_idx][R], STDIN_FILENO);
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][R]);
		wait(&(arg->status));
	}
}

void	connect_pipe(int cmd_idx, t_arg *arg)
{
	if (cmd_idx != arg->cmd_arg->cmd_count - 1)
	{
		if (dup2(arg->cmd_arg->fds[cmd_idx][W], STDOUT_FILENO) == -1)
			ft_error();
		close(arg->cmd_arg->fds[cmd_idx][W]);
		close(arg->cmd_arg->fds[cmd_idx][R]);
	}
}

void	connect_redir(t_redir *redir)
{
	t_redir	*temp;

	temp = redir;
	while (temp != 0)
	{
		if (sellect_redir(temp) == 0)
			ft_error();
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
