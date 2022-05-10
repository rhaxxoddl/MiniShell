/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:37:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/05/10 08:55:36 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parsing.h"

t_cmd_arg	*parsing(char **envp, char *line)
{
	t_cmd_arg	*cmd_arg;
	t_cmd		*temp_cmd;

	cmd_arg = (t_cmd_arg *)ft_calloc(1, sizeof(t_cmd_arg));
	temp_cmd = 0;
	if (cmd_arg == 0)
		ft_error();
	while (ft_isspace(*line))
		line++;
	while (*line != 0)
		add_cmd(cmd_arg, &temp_cmd, envp, &line);
	cmd_arg->fds = malloc_fds(cmd_arg->cmd_count);
	if (cmd_arg->fds == 0)
		ft_error();
	cmd_arg->path = get_path(envp);
	return (cmd_arg);
}

void	add_cmd(t_cmd_arg *cmd_arg, t_cmd **temp_cmd, char **envp, char **line)
{
	if (cmd_arg->cmd_count == 0)
	{
		(*temp_cmd) = parsing_cmd(envp, line);
		cmd_arg->cmd_head = (*temp_cmd);
		cmd_arg->cmd_count = 1;
		(*temp_cmd)->cmd_idx = 0;
	}
	else
	{
		(*temp_cmd)->next = parsing_cmd(envp, line);
		(*temp_cmd) = (*temp_cmd)->next;
		cmd_arg->cmd_count++;
		(*temp_cmd)->cmd_idx = cmd_arg->cmd_count - 1;
	}
}

t_cmd	*parsing_cmd(char **envp, char **line)
{
	t_cmd	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	cmd = init_cmd(line);
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"' ||
				(*line)[i] == '\\' || valid_dol(&(*line)[i]))
			parsing_cmd_routine(line, &temp, &i, envp);
		else if (get_redir_type(&(*line)[i]) && pro_before_str(&temp, line, &i))
		{
			if (temp != 0)
				cmd->cmd_p = add_col(cmd->cmd_p, &temp);
			parsing_redir(envp, cmd, line, &i);
		}
		else if (ft_isspace((*line)[i]))
			meet_space(line, &temp, &i, cmd);
		else
			i++;
	}
	parsing_cmd_finish(line, &temp, &i, cmd);
	return (cmd);
}

void	parsing_cmd_routine(char **line, char **temp, int *i, char **envp)
{
	if (valid_dol(&(*line)[*i]))
		pro_env(envp, temp, line, i);
	else if ((*line)[*i] == '\'')
		pro_s_quotes(temp, line, i);
	else if ((*line)[*i] == '\"')
		pro_d_quotes(envp, temp, line, i);
	else if ((*line)[*i] == '\\')
		pro_bslash(temp, line, i);
}

void	parsing_cmd_finish(char **line, char **temp, int *i, t_cmd *cmd)
{
	if (*i > 0 && !ft_isspace((*line)[(*i) - 1]))
	{
		*temp = app_str(*temp, ft_substr(*line, 0, (*i)));
		if (*temp == 0)
			ft_error();
	}
	if (*temp != 0)
	{
		cmd->cmd_p = add_col(cmd->cmd_p, temp);
		if (cmd->cmd_p == 0)
			ft_error();
	}
	if ((*line)[*i] == '|')
		(*line) = (*line) + (*i) + 1;
	else
		(*line) = (*line) + (*i);
}
