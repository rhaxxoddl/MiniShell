/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:26:10 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 10:50:10 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/wait.h>

int	run_process(t_arg *arg, t_cmd_arg *cmd_arg)
{
	pid_t	pid;

	if (arg->cmd_arg->cmd_count == 1
		&& chk_builtin(cmd_arg->cmd_head->cmd_p))
		return (exec_cmd_one(cmd_arg, cmd_arg->cmd_head->cmd_p, &(arg->envp)));
	pid = fork();
	if (pid == -1)
		ft_error();
	else if (pid == 0)
	{
		sig_init_child();
		while (cmd_arg->cmd_head != 0)
		{
			run_cmd(arg, cmd_arg->cmd_head);
			cmd_arg->cmd_head = cmd_arg->cmd_head->next;
		}
		exit_handle(arg);
	}
	else if (pid > 0)
	{
		waitpid(pid, &(arg->status), 0);
		update_status(&(arg->envp), WEXITSTATUS(arg->status));
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
		connect_redir(cmd_head->cmd_idx, arg->cmd_arg, cmd_head->redir);
		if (cmd_head->cmd_p[0] != 0)
			exec_cmd(cmd_head->cmd_p, &(arg->envp), arg->cmd_arg->path);
	}
	else if (pid > 0)
	{
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][W]);
		dup2(arg->cmd_arg->fds[cmd_head->cmd_idx][R], STDIN_FILENO);
		close(arg->cmd_arg->fds[cmd_head->cmd_idx][R]);
	}
}

void	connect_pipe(int cmd_idx, t_cmd_arg *cmd_arg)
{
	if (cmd_idx != cmd_arg->cmd_count - 1)
	{
		if (dup2(cmd_arg->fds[cmd_idx][W], STDOUT_FILENO) == -1)
			ft_error();
		close(cmd_arg->fds[cmd_idx][W]);
		close(cmd_arg->fds[cmd_idx][R]);
	}
}

void	connect_redir(int cmd_idx, t_cmd_arg *cmd_arg, t_redir *redir)
{
	t_redir	*temp;
	int		out;

	out = 0;
	temp = redir;
	while (temp != 0)
	{
		if (sellect_redir(temp, &out) == 0)
			ft_error();
		temp = temp->next;
	}
	if (out == 0)
		connect_pipe(cmd_idx, cmd_arg);
}

void	exit_handle(t_arg *arg)
{
	int	p_count;

	p_count = 0;
	while (p_count <= arg->cmd_arg->cmd_count)
	{
		wait(&(arg->status));
		p_count++;
	}
	if (WIFEXITED(arg->status))
		exit(WEXITSTATUS(arg->status));
	else if (WIFSIGNALED(arg->status))
		exit(WTERMSIG(arg->status));
}
