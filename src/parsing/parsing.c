/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanjeon <sanjeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 10:37:54 by sanjeon           #+#    #+#             */
/*   Updated: 2022/04/28 09:20:40 by sanjeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "parsing.h"

t_cmd_arg	*parsing(t_env *env_head, char *line)
{
	t_cmd_arg	*cmd_arg;
	t_cmd		*temp_cmd;

	cmd_arg = (t_cmd_arg *)ft_calloc(1, sizeof(t_cmd_arg));
	if (cmd_arg == 0)
		perror("");
	while (ft_isspace(*line))
		line++;
	while (*line != 0)
	{
		if (cmd_arg->cmd_count == 0)
		{
			temp_cmd = parsing_cmd(env_head, &line);
			cmd_arg->cmd_head = temp_cmd;
			cmd_arg->cmd_count = 1;
			temp_cmd->cmd_idx = 0;
		}
		else
		{
			temp_cmd->next = parsing_cmd(env_head, &line);
			temp_cmd = temp_cmd->next;
			cmd_arg->cmd_count++;
			temp_cmd->cmd_idx = cmd_arg->cmd_count - 1;
		}
	}
	cmd_arg->fds = malloc_fds(cmd_arg->cmd_count);
	if (cmd_arg->fds == 0)
		perror("");
	cmd_arg->path = get_path(env_head);
	return (cmd_arg);
}

t_cmd	*parsing_cmd(t_env *env_head, char **line)
{
	t_cmd	*cmd;
	char	*temp;
	int		i;

	i = 0;
	temp = 0;
	while (ft_isspace(**line))
		(*line)++;
	// 여기부터
	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (cmd == 0)
		perror("");
	cmd->cmd_param = (char **)ft_calloc(1, sizeof(char *));
	if (cmd->cmd_param == 0)
		perror("");
	cmd->redir = 0;
	// 여기까지 함수로 빼기
	while ((*line)[i] != 0 && (*line)[i] != '|')
	{
		if (valid_dol(&(*line)[i]))
		{
			if (!pro_env(env_head, &temp, line, &i))
				perror("");
		}
		else if ((*line)[i] == '\'')
		{
			if (!pro_s_quotes(&temp, line, &i))
				perror("");
		}
		else if ((*line)[i] == '\"')
		{
			if (!pro_d_quotes(env_head, &temp, line, &i))
				perror("");
		}
		else if (get_redir_type(&(*line)[i]))
		{
			if (!pro_before_str(&temp, line, &i))
				perror("");
			cmd->cmd_param = add_col(cmd->cmd_param, temp);
			if (!parsing_redir(env_head, cmd, line, &i))
				perror("");
		}
		else if (ft_isspace((*line)[i]))
		{
			temp = app_str(temp, ft_substr(*line, 0, i));
			cmd->cmd_param = add_col(cmd->cmd_param, temp);
			temp = 0;
			(*line) = (*line) + i;
			while (ft_isspace(**line))
				(*line)++;
			i = 0;
		}
		else
			i++;
	}
	if (i > 0 && !ft_isspace((*line)[i - 1]))
	{
		temp = app_str(temp, ft_substr(*line, 0, i));
		if (temp == 0)
			perror("");
	}
		cmd->cmd_param = add_col(cmd->cmd_param, temp);
		if (cmd->cmd_param == 0)
			perror("");
		temp = 0;
	if ((*line)[i] == '|')
		(*line) = (*line) + i + 1;
	else
		(*line) = (*line) + i;
	return (cmd);
}
